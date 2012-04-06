#include <iostream>
#include <sstream>

// Spécifique pour les sockets
#include <sys/types.h>  
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>

// Includes du projet
#include <WebServer.hpp>
#include <WebRequest.hpp>
#include <routes.hpp>

using namespace std;

// Important à faire quand on fait du patern singleton en C++
WebServer* WebServer::instance = NULL;

WebServer::WebServer(const int port) :
	logger("log/webserver.log")
{
	// Init générale
	this->isRunning = true;

	// Init de la socket
	this->port = port;
	this->serv_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	
	if (this->serv_socket < 0)
	{
		this->logger.put("error", "impossible d'ouvrir la socket.");
	}
	
	bzero((char *) &this->serv_addr, sizeof(this->serv_addr));
	
	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_addr.s_addr = INADDR_ANY;
	this->serv_addr.sin_port = htons(this->port);
	
	if (bind(this->serv_socket, (struct sockaddr *) &this->serv_addr, sizeof(this->serv_addr)) < 0)
	{
		this->logger.put("error", "impossible de binder la socket.");
	}
	
	// Listen avec un tampon de 5
	if (listen(this->serv_socket, 5) < 0)
	{
		this->logger.put("error", "impossible d'écouter sur le port demandé.");
	}
	
	// Init des routes
	this->routes.insert(pair<string, route_handler>("/", default_route));
	this->routes.insert(pair<string, route_handler>("/deployment", deployment_route));
	this->routes.insert(pair<string, route_handler>("/deployments", deployments_route));
	this->routes.insert(pair<string, route_handler>("/server", server_route));
	this->routes.insert(pair<string, route_handler>("/stop", stop_route));
	this->routes.insert(pair<string, route_handler>("/restart", restart_route));
}

WebServer::~WebServer()
{
	if (shutdown(this->serv_socket, 2) < 0)
	{
		this->logger.put("error", "impossible de fermer la socket du server.");
	}
}

WebServer* WebServer::getInstance()
{
	if (instance == NULL)
	{
		instance = new WebServer(WEBSERVER_PORT);
	}
	
	return instance;
}

void WebServer::run()
{
	char message[475];
	unsigned int size = sizeof(struct sockaddr);
	int nsock;
	
	while (this->isRunning)
	{
		/* acceptation connexion */
		nsock = accept(this->serv_socket, (struct sockaddr *) &this->cli_addr, &size);
		if (nsock < 0)
		{
			this->logger.put("error", "impossible d'accepter le client.");
		}

		/* lecture */
		if (read(nsock, message, 475*sizeof(char)) < 0)
		{
			this->logger.put("error", "impossible de lire le contenu de la socket.");
		}
		
		WebRequest request(message);
		string toReturn;
		
		// Vérifie que la route existe
		map<string, route_handler>::iterator it = this->routes.find(request.getTarget());
		if (it == routes.end())
		{
			toReturn = ressource_route(request);
		}
		else
		{
			toReturn = (*it).second(request);
		}
		
		write(nsock, toReturn.c_str(), toReturn.length() * sizeof(char));
		
		close(nsock);
	}
}

void WebServer::stop()
{
	this->isRunning = false;
	this->logger.put("notice", "le serveur a été arrêté.");
}

void WebServer::restart()
{
	this->logger.put("notice", "le serveur a été redémarré.");
}

