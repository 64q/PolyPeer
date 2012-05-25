// Class header
#include <PolypeerClient.hpp>

// STL
#include <iostream>

// Project header
#include <ClientData.hpp>
#include <PacketCallback.hpp>
#include <callbackFunctionClient.hpp>


using namespace std;

PolypeerClient* PolypeerClient::instance = NULL;

PolypeerClient::PolypeerClient() :
	BaseServer("log/PolypeerClient.log")
{
	logger.setVerboseMode(true);
	logger << "Lancement du client Polypeer..."<<endlog;


	// initialisation du system de callBack
	// -> permet l'appel "automatique des traitement pour un paquet
	PacketCallback * pcb = PacketCallback::getPacketCallback();
	pcb->addOperation (ESendChunk, callbackSendChunk);
	pcb->addOperation (ESendOperation, callbackSendOperation);

}

PolypeerClient::~PolypeerClient()
{

}

PolypeerClient* PolypeerClient::getInstance()
{
	if (instance == NULL)
	{
		instance = new PolypeerClient();
	}
	return instance;
}

void PolypeerClient::start()
{
	//sData = new ServerData();
	this->running = true;

	// ajouter connection avec serveur
	try
	{
		Socket sock(getClientData()->getIpServer(), getClientData()->getPortServer());
		getClientData()->getConnectionManager()->addConnection(getClientData()->getIpServer(), &sock);
	}
	catch(HostNotFoundException)
	{
		logger << "Impossible de contacter le serveur!" << endlog;
	}
	// Lancement du server
	this->run();
}

void PolypeerClient::restart()
{
	stop();
	sleep(5000);
	start();
}

void PolypeerClient::run()
{
	// propre à 'instance client polypeer
	PolypeerClient* server = PolypeerClient::getInstance();



}

void PolypeerClient::stop()
{
	this->running = false;
}
