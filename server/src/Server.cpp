#include <iostream>
#include <exception>
#include <map>

#include <Server.hpp>
#include <WebServer.hpp>
#include <Logger.hpp>
#include <Host.hpp>

using namespace std;

Server* Server::instance = NULL;

Server::Server() :
	BaseServer("log/server.log")
{
	this->webserver = WebServer::getInstance();
	this->running = true;
	
	this->logger.put("notice", "démarrage du serveur sur le port 9696.");
	
	this->webserver->setResourcesPath("../webserver/webpages");
}

Server* Server::getInstance()
{
	if (instance == NULL)
	{
		instance = new Server();
	}
	
	return instance;
}

Server::~Server()
{
	delete webserver;
}

void Server::start(const int port)
{
	this->port = port;
}

void Server::run()
{
	// Il faudra nécessairement threader cette partie puisque qu'il y aura au moins la socket
	// du serveur et la socket du serveur web.
	this->webserver->run();
}

void Server::stop()
{
	this->running = false;
	this->logger.put("notice", "le serveur a été arrêté.");
}

void Server::restart()
{
	this->logger.put("notice", "le serveur a été redémarré.");
}

Host Server::getHost(string name)
{
	map<string, Host>::iterator it = hosts.find(name);
	
	if (it  != hosts.end())
	{
		return (*it).second;
	}
	else
	{
		throw new exception;
	}
}
