#include <iostream>

#include <Server.hpp>
#include <WebServer.hpp>
#include <Logger.hpp>

using namespace std;

Server* Server::instance = NULL;

Server::Server(const int port) :
	logger("log/server.log")
{
	this->webserver = WebServer::getInstance();
	this->isRunning = true;
	
	this->logger.put("notice", "démarrage du serveur sur le port 9696.");
	
	this->webserver->setResourcesPath("../webserver/webpages");
}

Server* Server::getInstance(const int port)
{
	if (instance == NULL)
	{
		instance = new Server(port);
	}
	
	return instance;
}

Server::~Server()
{
	delete webserver;
}

void Server::run()
{
	// Il faudra nécessairement threader cette partie puisque qu'il y aura au moins la socket
	// du serveur et la socket du serveur web.
	this->webserver->run();
}

void Server::stop()
{
	this->isRunning = false;
	this->logger.put("notice", "le serveur a été arrêté.");
}

void Server::restart()
{
	this->logger.put("notice", "le serveur a été redémarré.");
}
