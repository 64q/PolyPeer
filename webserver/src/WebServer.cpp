#include <iostream>
#include <sstream>
#include <exception>
#include <cstring>

#include <mongoose.h>

#include <WebServer.hpp>
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
	routes.insert(pair<string, route_handler>("/ajax/state", state_route));
	routes.insert(pair<string, route_handler>("/ajax/home", home_route));
	routes.insert(pair<string, route_handler>("/ajax/deployment", deployment_route));
	routes.insert(pair<string, route_handler>("/ajax/deployments", deployments_route));
	routes.insert(pair<string, route_handler>("/ajax/topology", topology_route));
	routes.insert(pair<string, route_handler>("/ajax/new_deployment", new_deployment_route));
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
	
	if (this->context == NULL)
	{
		throw exception();
	}
}

void WebServer::run()
{
	// not implemented
}

void WebServer::stop()
{
	this->running = false;
	
	mg_stop(this->context);
	
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

void WebServer::call(mg_connection *conn, const mg_request_info *request_info)
{
	map<string, route_handler>::iterator it = routes.find(request_info->uri);
	
	if (it != routes.end()) 
	{
		it->second(conn, request_info);
	}
	else
	{
		routes.find("/ajax/error")->second(conn, request_info);
	}
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

	return const_cast<void*> (processed);
}
