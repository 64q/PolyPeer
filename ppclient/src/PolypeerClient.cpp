// Class header
#include <PolypeerClient.hpp>

// STL
#include <iostream>

// Project header
#include <ClientData.hpp>
#include <PacketCallback.hpp>
#include <callbackFunctionClient.hpp>


#ifdef WIN32 /* si vous êtes sous Windows */

#define sleep(t) Sleep(t)

#endif


using namespace std;

PolypeerClient* PolypeerClient::instance = NULL;

PolypeerClient::PolypeerClient() :
	BaseServer("log/ppclient.log")
{
	logger.setVerboseMode(true);
	logger << "Lancement du client Polypeer..."<<endlog;

	// initialisation du system de callBack
	// -> permet l'appel "automatique des traitement pour un paquet
	PacketCallback * pcb = PacketCallback::getPacketCallback();
	pcb->addOperation (ENewFile, callbackNewFile);
	pcb->addOperation (ESendChunk, callbackSendChunk);
	pcb->addOperation (ESendOperation, callbackSendOperation);
	pcb->addOperation(ERemoveHost, callbackRemoveHost);
	pcb->addOperation(EPacketInvalid, callbackPacketInvalid);

}

PolypeerClient::~PolypeerClient()
{

}

void PolypeerClient::setConfig(ClientOptions* opt)
{
	cData = new ClientData(opt);
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
		logger << "tentative de contact du serveur!" << endlog;
		Socket* sock = new Socket(getClientData()->getAddressServ(), getClientData()->getPortServ());
		logger << "connexion au serveur "<<getClientData()->getAddressServ()<<":"<<getClientData()->getPortServ()<<" réussie"<<endlog;
		getClientData()->getConnectionManager()->addConnection(getClientData()->getAddressServ(), sock);
		logger << "tentative réussi contact du serveur!" << endlog;
	}
	catch(HostNotFoundException)
	{
		logger << "Impossible de contacter le serveur!" << endlog;
	}
	catch(ConnectionException)
	{
		logger << "Impossible de contacter le serveur!" << endlog;
	}
	// Lancement du server
	this->run();
}

void PolypeerClient::restart()
{
	stop();
	sleep(5);
	start();
}

void PolypeerClient::run()
{
	// propre à l'instance client polypeer
	PolypeerClient::getInstance()->getClientData()->getConnectionManager()->wait();
	cout << "client terminé"<<endl;
}

void PolypeerClient::stop()
{
	this->running = false;
	delete cData;
}
