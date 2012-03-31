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
		cerr << "Erreur d'ouverture de la socket..." << endl;
	}
	else
	{
		cout << "Création de la socket réussie." << endl;
	}
	
	bzero((char *) &this->serv_addr, sizeof(this->serv_addr));
	
	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_addr.s_addr = INADDR_ANY;
	this->serv_addr.sin_port = htons(this->port);
	
	if (bind(this->socket, (struct sockaddr *) &this->serv_addr, sizeof(this->serv_addr)) < 0)
	{
		cerr << "Erreur, impossible de binder la socket..." << endl;
	}
	else
	{
		cout << "Binding de la socket réussie." << endl;
	}
	
	// Listen avec un tampon de 5
	if (listen(this->socket, 5) < 0)
	{
		cerr << "Erreur, impossible de faire écouter la socket..." << endl;
	}
	else
	{
		cout << "Listen de la socket réussi." << endl;
	}
	
	// Init des routes
	this->routes.insert(pair<string, route_handler>("/", default_route));
}

WebServer::~WebServer()
{
	if (close(this->socket) < 0)
	{
		cerr << "Erreur lors de la fermeture du descripteur de fichier." << endl;
	}
	else
	{
		cout << "Socket détruite." << endl;
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
			cerr << "Erreur lors de l'acceptation de la connexion d'un client..." << endl;
		}
		else
		{
			cout << "Acceptation du client réussie." << endl;
		}

		/* lecture */
		if (read(nsock, message, 475*sizeof(char)) < 0)
		{
			cerr << "Erreur lors de la lecture du contenu..." << endl;
		}
		
		WebRequest request(message);
		string toReturn;
		
		// Vérifie que la route existe
		map<string, route_handler>::iterator it;
		if (this->routes.find(request.getTarget()) == routes.end())
		{
			// Redirection vers page d'erreur
			toReturn = notfound_route(request);
		}
		else
		{
			toReturn = routes[request.getTarget()](request);
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
	// Contenu
	ostringstream content(ostringstream::out);
	content << "<h1>PolyPeer WebServer</h1>\n";
	content << "<h2>Powered by Quentin</h2>\n";
	content << "<p>Bienvenue "; content << request.getParam("username");
	content << " !</p>\n";
	content << "<a href=\"/login\">Se connecter</a>\n";
	
	// Header
	ostringstream response(ostringstream::out);
	response << "HTTP/1.0 200 OK\n";
	response << "Content-Type: text/html; charset=utf-8\n";
	response << "Content-Length: ";
	response << content.str().length(); response << "\n";
	response << "Connection: close\n\n";
	
	string str_response(response.str());
	string str_content(content.str());
	
	str_response += str_content;
	
	return str_response;
}

string notfound_route(WebRequest& request)
{
	// Contenu
	ostringstream content(ostringstream::out);
	content << "<h1>Page introuvable</h1>\n";
	content << "<h2>Powered by Quentin</h2>\n";
	content << "<p>La page que vous avez demandé n'existe pas.</p>";
	content << "<a href=\"/\">Retour index</a>\n";
	
	// Header
	ostringstream response(ostringstream::out);
	response << "HTTP/1.0 200 OK\n";
	response << "Content-Type: text/html; charset=utf-8\n";
	response << "Content-Length: ";
	response << content.str().length(); response << "\n";
	response << "Connection: close\n\n";
	
	string str_response(response.str());
	string str_content(content.str());
	
	str_response += str_content;
	
	return str_response;
}
