#include <iostream>
#include <sstream>

// Spécifique pour les sockets
#include <sys/types.h>  
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../include/WebServer.hpp"
#include "../include/WebRequest.hpp"
#include "../include/routes.hpp"

using namespace std;

// Important à faire quand on fait du patern singleton en C++
WebServer* WebServer::instance = NULL;

WebServer::WebServer(const int port)
{
	// Init générale
	this->isRunning = true;

	// Init de la socket
	this->port = port;
	this->serv_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	
	if (this->serv_socket < 0)
	{
		cerr << "(server) Erreur d'ouverture de la socket..." << endl;
	}
	else
	{
		cout << "(server) Création de la socket réussie." << endl;
	}
	
	bzero((char *) &this->serv_addr, sizeof(this->serv_addr));
	
	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_addr.s_addr = INADDR_ANY;
	this->serv_addr.sin_port = htons(this->port);
	
	if (bind(this->serv_socket, (struct sockaddr *) &this->serv_addr, sizeof(this->serv_addr)) < 0)
	{
		cerr << "(server) Erreur, impossible de binder la socket..." << endl;
	}
	else
	{
		cout << "(server) Binding de la socket réussie." << endl;
	}
	
	// Listen avec un tampon de 5
	if (listen(this->serv_socket, 5) < 0)
	{
		cerr << "(server) Erreur, impossible de faire écouter la socket..." << endl;
	}
	else
	{
		cout << "(server) Listen de la socket réussi." << endl;
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
		cerr << "(server) Erreur lors de la fermeture de la socket serveur." << endl;
	}
	else
	{
		cout << "(server) Socket serveur détruite." << endl;
	}
	
	if (shutdown(this->cli_socket, 2) < 0)
	{
		cerr << "(server) Erreur lors de la fermeture de la socket client." << endl;
	}
	else
	{
		cout << "(server) Socket client détruite." << endl;
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
	
	while (this->isRunning)
	{
		/* acceptation connexion */
		this->cli_socket = accept(this->serv_socket, (struct sockaddr *) &this->cli_addr, &size);
		if (this->cli_socket < 0)
		{
			cerr << "(server) Erreur lors de l'acceptation de la connexion d'un client..." << endl;
		}

		/* lecture */
		if (read(this->cli_socket, message, 475*sizeof(char)) < 0)
		{
			cerr << "(server) Erreur lors de la lecture du contenu..." << endl;
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
			cout << "(server) Le client a demandé la page : "<< request.getTarget() << endl;
		}
		
		write(this->cli_socket, toReturn.c_str(), toReturn.length() * sizeof(char));
		
		close(this->cli_socket);
	}
}

void WebServer::stop()
{
	this->isRunning = false;
}

void WebServer::restart()
{
	// Pas implémentée
}

