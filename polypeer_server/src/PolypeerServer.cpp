#include <iostream>

#include <PolypeerServer.hpp>

using namespace std;


PolypeerServer::PolypeerServer() :
	//BaseServer("log/PolypeerServer.log")
	running(false)
{

}

PolypeerServer::~PolypeerServer()
{

}


void PolypeerServer::start()
{
	this->running = true;
	// Lancement du serveur
	this->run();
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

void PolypeerServer::restart()
{
	
}


