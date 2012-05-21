#include <iostream>

#include <PolypeerServer.hpp>

using namespace std;


PolypeerServer* PolypeerServer::instance = NULL;

PolypeerServer::PolypeerServer() :
	running(false),
	port(6969),
	logger("log/PolypeerServer.log")
{
	logger.setVerboseMode(true);
	logger << "Lancement du serveur Polypeer..."<<endLog;
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
	this->running = true;
	// Lancement du serveur
	this->run();
}

void PolypeerServer::restart()
{
	stop();
	start();
}

void PolypeerServer::run()
{
	while(running)
	{
		
	}
}

void PolypeerServer::stop()
{
	this->running = false;
}

Logger& PolypeerServer::getLogger()
{
	return logger;
}

