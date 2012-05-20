#include <iostream>
#include <sstream>
#include <exception>
#include <cstring>

#include <mongoose.h>

#include <WebServer.hpp>

using namespace std;

static const char *mg_options[] = {
  "document_root", "html",
  "listening_ports", "6969",
  "num_threads", "5",
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

void* eventHandler(mg_event event, mg_connection *conn, const mg_request_info *request_info)
{
	const void *processed = "yes";

	if (event == MG_NEW_REQUEST) {
		if (strcmp(request_info->uri, "/test") == 0) {
			processed = NULL;
		} else {
			processed = NULL;
		}
	} else {
		processed = NULL;
	}

	return const_cast<void*> (processed);
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

