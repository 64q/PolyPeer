// Class header
#include <PolypeerServer.hpp>

// STL
#include <iostream>
#include <set>

// C lib
#include <pthread.h>

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
	BaseServer("log/ppserver.log")
{
	logger.setVerboseMode(true);
	logger << "Le serveur Polypeer a été démarré sur le port " << this->port << endlog;

	// récupération du logger
	webserver = WebServer::getInstance();

	// initialisation du system de callBack
	// -> permet l'appel "automatique des traitement pour un paquet
	PacketCallback * pcb = PacketCallback::getPacketCallback();
	pcb->addOperation (EReady, callbackReady);
	pcb->addOperation (EChunkReceived, callbackChunkReceived);
	pcb->addOperation (EMd5Error, callbackMd5Error);
	pcb->addOperation (EDiskFull, callbackPacketDiskFull);
	pcb->addOperation (ESendOperationFinished, callbackPacketSendOperationFinished);
	pcb->addOperation (EAddHost, callBackAddHost);
	pcb->addOperation (ERemoveHost, callbackRemoveHost);
}

PolypeerServer::~PolypeerServer()
{
	delete sData;
	delete webserver;
}

PolypeerServer* PolypeerServer::getInstance()
{
	if (instance == NULL)
	{
		instance = new PolypeerServer();
	}
	return instance;
}

void PolypeerServer::setConfig(ServerOptions* opt)
{
	sData = new ServerData(opt);
}

void PolypeerServer::start()
{
	//sData = new ServerData();
	this->running = true;
	// Lancement du webserveur
	webserver->start();

	// initialisation des connexions
	initConnections();

	// Lancement du server
	this->run();
}

void PolypeerServer::restart()
{
	stop();
	multiSleep(10000);
	start();
}

void PolypeerServer::run()
{
	// propre à 'instance serveur polypeer
	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();

	// Algorithme de déploiment
	DeploymentAlgorithm* algo = new ShareDeployment(server, &data);


	PolypeerServer::getInstance()->logger<< "waiting 2 seconds to bind socket..." << endlog;
	PolypeerServer::getInstance()->multiSleep(2000);

	while (server->running)
	{

		// Execution d'une étape de l'algo
		algo->nextStep();

		// waiting time
		//PolypeerServer::getInstance()->multiSleep(100);
	}

	delete algo;
}

void PolypeerServer::stop()
{
	webserver->stop();
	(PolypeerServer::instance)->getLogger()<<"Le serveur a été arrêté." <<endlog;
	this->running = false;
}


void  PolypeerServer::initConnections()
{
	// liste des déploiements
	vector<File*>* files = sData->getDeployFiles();

	ConnectionManager* cm = sData->getConnectionManager();

	set<Entity*> myHostSet;

	for (vector<File*>::iterator itFile = files->begin(); itFile != files->end(); itFile++)
	{
		if(((*itFile)->getFileState() == READY) || ((*itFile)->getFileState() == DEPLOYMENT))
		{
			vector<Entity*>* hosts = (*itFile)->getDeploysOn();

			for (vector<Entity*>::iterator itHost = hosts->begin(); itHost != hosts->end(); itHost++)
			{
				myHostSet.insert((*itHost));
			}
		}
	}

	for (set<Entity*>::iterator itHost = myHostSet.begin(); itHost != myHostSet.end(); itHost++)
	{
		pthread_t myThread;
		if(cm->getConnection((*itHost)->getIP()) == NULL)
		{
			pthread_create(&myThread, NULL, thread_initConnection, (*itHost));
		}
	}
}


void* thread_initConnection(void* data)
{
	ConnectionManager* cm = (PolypeerServer::instance)->getServerData().getConnectionManager();
	Host* myHost = (Host*)data;
	try
	{
		Socket* socket = new Socket(myHost->getIP(), (PolypeerServer::instance)->getServerData().getClientPort());
		cm->addConnection(myHost->getIP(), socket);
		myHost->setHostState(WAIT);
	} catch(ConnectionException)
	{
		//(PolypeerServer::instance)->getLogger()<<"Connection to " << myHost->getIP() << " failed" <<endlog;


		/*A tester en condition réelle!!

		ConnectionManager::WOL(myHost->getMAC(), myHost->getMask());
		*/
	}


	return NULL;
}



