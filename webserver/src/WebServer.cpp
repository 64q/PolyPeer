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
#include "../include/WebResponse.hpp"
#include "../include/TinyParser.hpp"

using namespace std;

// Important à faire quand on fait du patern singleton en C++
WebServer* WebServer::instance = NULL;

WebServer::WebServer(const int port)
{
	// Init générale
	this->isRunning = true;

	// Init de la socket
	this->port = port;
	this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
	
	if (this->socket < 0)
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
	
	if (bind(this->socket, (struct sockaddr *) &this->serv_addr, sizeof(this->serv_addr)) < 0)
	{
		cerr << "(server) Erreur, impossible de binder la socket..." << endl;
	}
	else
	{
		cout << "(server) Binding de la socket réussie." << endl;
	}
	
	// Listen avec un tampon de 5
	if (listen(this->socket, 5) < 0)
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
}

WebServer::~WebServer()
{
	if (close(this->socket) < 0)
	{
		cerr << "(server) Erreur lors de la fermeture du descripteur de fichier." << endl;
	}
	else
	{
		cout << "(server) Socket détruite." << endl;
	}
	
}

WebServer* WebServer::getInstance()
{
	if (instance == NULL)
	{
		instance = new WebServer(6969);
	}
	
	return instance;
}

void WebServer::run()
{
	int nsock;
	char message[475];
	unsigned int size = sizeof(struct sockaddr);
	
	while (this->isRunning)
	{
		/* acceptation connexion */
		nsock = accept(this->socket, (struct sockaddr *) &this->cli_addr, &size);
		if (nsock < 0)
		{
			cerr << "(server) Erreur lors de l'acceptation de la connexion d'un client..." << endl;
		}

		/* lecture */
		if (read(nsock, message, 475*sizeof(char)) < 0)
		{
			cerr << "(server) Erreur lors de la lecture du contenu..." << endl;
		}
		
		WebRequest request(message);
		string toReturn;
		
		// Vérifie que la route existe
		map<string, route_handler>::iterator it = this->routes.find(request.getTarget());
		if (it == routes.end())
		{
			// Redirection vers page d'erreur
			toReturn = notfound_route(request);
			cout << "(server) Le client a demandé une page qui n'existe pas. (TARGET=" << request.getTarget() << ")" << endl;
		}
		else
		{
			toReturn = (*it).second(request);
			cout << "(server) Le client a demandé la page : "<< request.getTarget() << endl;
		}
		
		write(nsock, toReturn.c_str(), toReturn.length() * sizeof(char));
		
		close(nsock);
	}
}

void WebServer::stop()
{
	this->isRunning = false;
}

string default_route(WebRequest& request)
{
	TinyParser parser("webpages/default.html");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string deployment_route(WebRequest& request)
{
	TinyParser parser("webpages/deployment.html");
	
	parser.inject("deploy", request.getParam("deploy"));
	parser.inject("state", "actif");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string notfound_route(WebRequest& request)
{
	TinyParser parser("webpages/error404.html");
	
	WebResponse response(404, parser.render());
	return response.getRawData();
}
