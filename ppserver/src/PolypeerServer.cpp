#include <iostream>

#include <BaseServer.hpp>
#include <PolypeerServer.hpp>

using namespace std;


PolypeerServer* PolypeerServer::instance = NULL;

PolypeerServer::PolypeerServer() :
	BaseServer("log/PolypeerServer.log")
{
	logger.setVerboseMode(true);
	logger << "Lancement du serveur Polypeer..."<<endlog;
	webserver = WebServer::getInstance();
}

PolypeerServer::~PolypeerServer()
{

}

PolypeerServer* PolypeerServer::getInstance()
{
	if (instance == NULL)
	{
		instance = new PolypeerServer();
	}
	return instance;
}

void PolypeerServer::start()
{
	//sData = new ServerData();
	this->running = true;
	// Lancement du webserveur
	webserver->start();
	// Lancement du server
	this->run();
}

void PolypeerServer::restart()
{
	stop();
	sleep(5000);
	start();
}

void PolypeerServer::run()
{
	PolypeerServer* server = PolypeerServer::getInstance();
	
	while (server->running)
	{
		
	}
}

void PolypeerServer::stop()
{
	webserver->stop();
	this->running = false;
}

