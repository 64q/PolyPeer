#include <iostream>
#include <sstream>
#include <exception>
#include <cstring>

#include <mongoose.h>

#include <WebServer.hpp>
#include <WebServerException.hpp>
#include <Logger.hpp>
#include <routes.hpp>

using namespace std;

static const char *mg_options[] = {
  "document_root", "html",
  "listening_ports", "6969",
  "num_threads", "5",
  "global_passwords_file", "passwd",
  "authentication_domain", "polypeer.polytech.prive",
  NULL
};

// Important à faire quand on fait du patern singleton en C++
WebServer* WebServer::instance = NULL;

WebServer::WebServer() :
	BaseServer("log/webserver.log")
{
	this->port = 6969;
	this->debug	= false;
	this->running = true;
	
	// insertion des routes
	routes.insert(pair<string, route_handler>("/ajax/error", error_route));
	routes.insert(pair<string, route_handler>("/ajax/get_stats", get_stats_route));
	routes.insert(pair<string, route_handler>("/ajax/get_host", get_host_route));
	routes.insert(pair<string, route_handler>("/ajax/deployment", deployment_route));
	routes.insert(pair<string, route_handler>("/ajax/deployments", deployments_route));
	routes.insert(pair<string, route_handler>("/ajax/network", network_route));
	routes.insert(pair<string, route_handler>("/ajax/new_deployment", new_deployment_route));
	routes.insert(pair<string, route_handler>("/ajax/pause_deployments", pause_deployments_route));
	routes.insert(pair<string, route_handler>("/ajax/pause_deployment", pause_deployment_route));
	routes.insert(pair<string, route_handler>("/ajax/unpause_deployment", unpause_deployment_route));
}

WebServer::~WebServer()
{

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
	// Lancement du serveur
	this->context = mg_start(eventHandler, NULL, mg_options);
	
	logger << notice << "Le serveur web a été démarré sur le port " << this->port << "." << endlog;
	
	if (this->context == NULL)
	{
		throw WebServerException();
	}
}

void WebServer::run()
{
	// Non implémenté
}

void WebServer::stop()
{
	this->running = false;
	
	mg_stop(this->context);
	
	logger << notice << "Le serveur web a été arrêté." << endlog;
	
	cout << "Arrête toi connard" << endl;
}

void WebServer::restart()
{
	this->stop();
	sleep(5);
	this->start();
	logger << notice << "Le serveur web a été redémarré." << endlog;
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

void* eventHandler(mg_event event, mg_connection *conn, const mg_request_info *request_info)
{
	const void *processed = "yes";

	WebServer* webserver	= WebServer::getInstance();
	
	if (event == MG_NEW_REQUEST) {
		map<string, route_handler>::iterator it = webserver->routes.find(request_info->uri);

		if (it != webserver->routes.end()) 
		{
			it->second(conn, request_info);
		}
		else
		{
			processed = NULL;
		}
	} else {
		processed = NULL;
	}
	
	if (webserver->isDebug()) {
		webserver->getLogger() << debug << "Route appelée '" << request_info->uri << "' avec les paramètres '" << request_info->query_string << "." << endlog;
	}

	return const_cast<void*> (processed);
}
