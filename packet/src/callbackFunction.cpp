#include <callbackFunction.hpp>



int callbackNewFile (Packet& p)
{
	PacketNewFile pp (p);

	cout << "callbackNewFile" << endl;


	Packet pReturn;

	// récupérer singleton serveur
	ServerData* sd = ServerData::getInstance();

	// -> un filemanager existe deja pour le fichier ? info ifFile et fileName
	FileManager* fm = sd->getFileManager(pp.getIdFile());
	if (fm == NULL)
	{
		// création du fileManager
		//try
		{
			fm = sd->addFile(pp.getIdFile(), pp.getFileName(), pp.getFileSize(), pp.getChunkSize());
		}/* catch (ExceptionDiskFull)
		{
			// Création du paquet d'erreur
			pReturn = PacketDiskFull (pp.getIdFile());
			return 0;
		}*/
	}

	// -> récuppérer le chunk courant
	pReturn = PacketReady (pp.getIdFile(), fm->getCurrentNumberChunk());

	// -> créer le nouveau paquet PacketReady
	sd->getConnectionManager()->sendTo(sd->getAddressServ(), pReturn);

	return 1;
}

int callbackSendOperation (Packet& p)
{
	PacketSendOperation pp (p);

	cout << "callbackSendOperation" << endl;
	
	// récupérer singleton serveur
	ServerData* sd = ServerData::getInstance();
	
	// vérifier que l'on possède bien le chunk en question
	// --
	Chunk c = pp.getChunk();
	// envoie à la cible
	sd->getConnectionManager()->sendTo(pp.getTarget(), PacketSendChunk(c));
	
	// réponse au serveur du travail effectué
	sd->getConnectionManager()->sendTo(sd->getAddressServ(), PacketSendOperationFinished());

	return 1;
}

int callbackSendChunk (Packet& p)
{
	PacketSendChunk pp (p);

	cout << "callbackSendChunk" << endl;

	// récupérer singleton serveur
	ServerData* sd = ServerData::getInstance();

	Chunk tmp(pp.getChunk());

	if(tmp.isIntegrate())
    {
    	FileManager* fm = sd->getFileManager(tmp.getIdFile());
        fm->saveChunk(tmp);

        sd->getConnectionManager()->sendTo(sd->getAddressServ(), PacketChunkReceived(tmp.getIdFile(), tmp.getNumber()));
    }
    else
    {
        // probleme de fichier
        sd->getConnectionManager()->sendTo(sd->getAddressServ(), PacketMd5Error(tmp.getIdFile(), tmp.getNumber()));
    }

	return 1;
}

int callbackReady (Packet& p)
{
	PacketReady pp (p);

	cout << "callbackIsReady" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost (src, pp.getIdFile(), pp.getChunkNumber());

	return 1;
}

int callbackChunkReceived (Packet& p)
{
	PacketChunkReceived pp (p);

	cout << "callbackChunkReceived" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost(src, pp.getIdFile(), pp.getChunkNumber());

	return 1;
}

int callbackMd5Error (Packet& p)
{
	PacketMd5Error pp (p);

	cout << "callbackMd5Error" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost(src, pp.getIdFile(), WAIT);
	
	return 1;
}

int callbackPacketDiskFull (Packet& p)
{
	PacketDiskFull pp (p);

	cout << "callbackPacketDiskFull5Error" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost(src, pp.getIdFile(), FULL);
	
	return 1;
}

int callbackPacketSendOperationFinished (Packet& p)
{
	PacketSendOperationFinished pp (p);

	cout << "callbackPacketSendOperationFinished" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost(src, WAIT);
	
	return 1;
}




