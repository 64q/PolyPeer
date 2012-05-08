#include <iostream>
#include <sstream>

#include <WebServer.hpp>
#include <WebRequest.hpp>
#include <routes.hpp>

using namespace std;

// Important à faire quand on fait du patern singleton en C++
WebServer* WebServer::instance = NULL;

WebServer::WebServer() :
	BaseServer("log/webserver.log"), resourcesPath("webpages")
{
	this->port = 6969;
	this->debug	= false;
	this->running = true;
	
	// Init des routes
	this->routes.insert(pair<string, route_handler>("/", default_route));
	this->routes.insert(pair<string, route_handler>("/deployment", deployment_route));
	this->routes.insert(pair<string, route_handler>("/deployments", deployments_route));
	this->routes.insert(pair<string, route_handler>("/server", server_route));
	this->routes.insert(pair<string, route_handler>("/stop", stop_route));
	this->routes.insert(pair<string, route_handler>("/restart", restart_route));
	this->routes.insert(pair<string, route_handler>("/debug", debug_route));
	this->routes.insert(pair<string, route_handler>("/toggledebug", toggledebug_route));
}

WebServer::~WebServer()
{
	this->socket->close();
	
	delete socket;
}

WebServer* WebServer::getInstance()
{
	if (instance == NULL)
	{
		instance = new WebServer();
	}
	
	return instance;
}

void WebServer::start()
{
	this->socket = new ServerSocket(this->port);
	
	// Lancement du serveur
	this->run();
}

void WebServer::run()
{
	char message[475];
	Socket* nsock;
	
	while (this->running)
	{
		/* acceptation connexion */
		nsock = this->socket->accept();

		/* lecture */
		nsock->read(message, 475*sizeof(char));
		
		WebRequest request(message);
		string sent;
		
		// Vérifie que la route existe
		map<string, route_handler>::iterator it = this->routes.find(request.getTarget());
		if (it == routes.end())
		{
			sent = resource_route(request);
		}
		else
		{
			sent = (*it).second(request);
		}
		
		nsock->send(sent.c_str(), sent.length() * sizeof(char));
		
		nsock->close();
	}
}

void WebServer::stop()
{
	this->running = false;
	this->socket->close();
	this->logger.put("notice", "le serveur a été arrêté.");
}

void WebServer::restart()
{
	this->logger.put("notice", "le serveur a été redémarré.");
}

void WebServer::toggleDebug()
{
	if (this->debug)
	{
		this->debug = false;
	}
	else
	{
		this->debug = true;
	}
}

bool WebServer::isDebug()
{
	return this->debug;
}

void WebServer::setResourcesPath(const std::string& path)
{
	this->resourcesPath = path;
}

string WebServer::getResourcesPath()
{
	 return this->resourcesPath;
}

