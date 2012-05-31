// Class header
#include <callbackFunctionClient.hpp>

// STL
#include <iostream>

// Project header
#include <PolypeerClient.hpp>
#include <ClientData.hpp>
#include <Packet.hpp>
#include <includePacket.hpp>
#include <DiskFullException.hpp>


using namespace std;

int callbackNewFile(Packet& p)
{
	PacketNewFile pp (p);

	cout << "callbackNewFile" << endl;


	Packet pReturn;

	// récupérer singleton serveur
	ClientData* cd = PolypeerClient::getInstance()->getClientData();
	// -> un filemanager existe deja pour le fichier ? info ifFile et fileName
	FileManager* fm = cd->getFileManager(pp.getIdFile());
	if (fm == NULL)
	{
		// création du fileManager
		try
		{
			fm = new FileManager(pp.getFileName().c_str(), pp.getFileSize(), pp.getChunkSize(), pp.getIdFile());
			cd->addFileManager(fm);
			cout << "création du fichier"<<endl;
		} catch (DiskFullException e)
		{
			// Création du paquet d'erreur
			cout << "full"<<endl;
			pReturn = PacketDiskFull (pp.getIdFile());
			return 0;
		}
	}

	// -> récuppérer le chunk courant
	pReturn = PacketReady (pp.getIdFile(), fm->getCurrentNumberChunk());
	cout << "chunk désiré n° " << fm->getCurrentNumberChunk() << endl;
	// -> créer le nouveau paquet PacketReady
	cd->getConnectionManager()->sendTo(cd->getAddressServ(), pReturn);

	return 1;
}

int callbackSendOperation(Packet& p)
{
	PacketSendOperation pp (p);

	cout << "callbackSendOperation" << endl;

	// récupérer singleton serveur
	ClientData* cd = PolypeerClient::getInstance()->getClientData();

	// vérifier que l'on possède bien le chunk en question
	// --
	FileManager* fm = cd->getFileManager(pp.getIdFile());
	
	cout <<" on demande a envoyé le "<<pp.getNumChunk()<<" du fichier "<< pp.getIdFile() <<endl;
	
	if(fm!=NULL)
	{
		Chunk c = fm->getChunk((long)pp.getNumChunk());
		cout << "Chunk prêt à envoyer n°" << c.getNumber()<<endl;
		// envoie à la cible
		cd->getConnectionManager()->sendTo(pp.getTarget(), PacketSendChunk(c));
		cout << "Chunk envoyé"<<endl;
		// réponse au serveur du travail effectué
		cd->getConnectionManager()->sendTo(cd->getAddressServ(), PacketSendOperationFinished());
		cout << "serveur prévenu"<<endl;
	
	}else
	{
	
		cout << "Ce fichier n'existe pas"<<endl;
	}
	

	return 1;
}

int callbackSendChunk(Packet& p)
{
	PacketSendChunk pp (p);

	cout << "callbackSendChunk" << endl;

	// récupérer singleton serveur
	ClientData* cd = PolypeerClient::getInstance()->getClientData();

	Chunk tmp(pp.getChunk());

	if(tmp.isIntegrate())
    {

    	FileManager* fm = cd->getFileManager(tmp.getIdFile());
        fm->saveChunk(tmp);

        cd->getConnectionManager()->sendTo(cd->getAddressServ(), PacketChunkReceived(tmp.getIdFile(), fm->getCurrentNumberChunk()));
    }
    else
    {
        cout << "erreur du Chunk reçu :";
        cout << tmp.getNumber()<<endl;
        cd->getConnectionManager()->sendTo(cd->getAddressServ(), PacketMd5Error(tmp.getIdFile(), tmp.getNumber()));
    }

	return 1;
}

int callbackRemoveHost(Packet& p)
{
	PacketRemoveHost pp(p);

	cout << "callbackRemoveHost" << endl;

	ClientData* cd = PolypeerClient::getInstance()->getClientData();
	ConnectionManager* cm = cd->getConnectionManager();
	cm->removeConnection(pp.getIpAddress());
	
	return 1;
}





