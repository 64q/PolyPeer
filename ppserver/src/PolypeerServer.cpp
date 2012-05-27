// Class header
#include <PolypeerServer.hpp>

// STL
#include <iostream>

// Project header
#include <ServerData.hpp>
#include <WebServer.hpp>
#include <PacketCallback.hpp>
#include <callbackFunctionServer.hpp>
#include <DeploymentAlgorithm.hpp>
#include <ShareDeployment.hpp>


using namespace std;

PolypeerServer* PolypeerServer::instance = NULL;

PolypeerServer::PolypeerServer() :
	BaseServer("log/PolypeerServer.log"),
	clientPort(5555)
{
	logger.setVerboseMode(true);
	logger << "Lancement du serveur Polypeer..."<<endlog;
	webserver = WebServer::getInstance();

	sData = new ServerData();
	
	// initialisation du system de callBack
	// -> permet l'appel "automatique des traitement pour un paquet
	PacketCallback * pcb = PacketCallback::getPacketCallback();
	pcb->addOperation (EReady, callbackReady);
	pcb->addOperation (EChunkReceived, callbackChunkReceived);
	pcb->addOperation (EMd5Error, callbackMd5Error);
	pcb->addOperation (EDiskFull, callbackPacketDiskFull);
	pcb->addOperation (ESendOperationFinished, callbackPacketSendOperationFinished);
}

PolypeerServer::~PolypeerServer()
{
	delete sData;
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
	
	// initialisation des connexions
	
	
	// Lancement du server
	this->run();
}

void PolypeerServer::restart()
{
	stop();
	sleep(10);
	start();
}

void PolypeerServer::run()
{
	// propre à 'instance serveur polypeer
	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();
	
	// Algorithme de déploiment
	DeploymentAlgorithm* algo = new ShareDeployment(server, &data);
	
	
	cout<< "Lancement Algo de décision" << endl;
	
	while (server->running)
	{

		// Execution d'une étape de l'algo
		algo->nextStep();
		
		// waiting time
		sleep(5);
	}
	
	delete algo;
}

void PolypeerServer::stop()
{
	webserver->stop();
	this->running = false;
}

void  PolypeerServer::initConnections()
{
	// liste des déploiements
	vector<File*>* files = sData->getDeployFiles();
	
	ConnectionManager* cm = sData->getConnectionManager();
	
	for (vector<File*>::iterator itFile = files->begin(); itFile != files->end(); itFile++) 
	{
		vector<Entity*>* hosts = (*itFile)->getDeploysOn();
		
		for (vector<Entity*>::iterator itHost = hosts->begin(); itHost != hosts->end(); itHost++) 
		{
			if(cm->getConnection((*itHost)->getIP()) == NULL)
			{
				Socket* socket = new Socket((*itHost)->getIP(), clientPort);
				cm->addConnection((*itHost)->getIP(), socket);
			}
		}
	}
}

