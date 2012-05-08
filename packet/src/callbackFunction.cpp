#include <callbackFunction.hpp>


int callbackAreYouReady (Packet& p)
{
	PacketAreYouReady pp(p);

	cout << "callbackAreYouReady" << endl;

	return 1;
}

int callbackNewFile (Packet& p)
{
	PacketNewFile pp (p);
	
	cout << "callbackNewFile" << endl;
	
	
	Packet pReturn;
	
	// récupérer singleton serveur
	ServerData* sd = ServerData.getInstance();

	// -> un filemanager existe deja pour le fichier ? info ifFile et fileName
	FileManager* fm = sd->getFileManager(pp.getIdFile());
	if (fm == NULL)
	{
		// création du fileManager
		try
		{
			fm = sd->addFileManager(pp.getIdFile(), pp.getFileName(), pp.getFileSize(), pp.getChunkSize());
		} catch (ExceptionDiskFull)
		{
			// Création du paquet d'erreur
			pReturn = PacketDiskFull (pp.getIdFile());
			return 0;
		}
	} 
	
	// -> récuppérer le chunk courant
	pRetrun = PacketReady (pp.getIdFile(), fm->getCurrentNumberChunk())

	// -> créer le nouveau paquet PacketReady
	sd->send(pReturn);
	
	return 1;
}

int callbackSendOperation (Packet& p)
{
	PacketSendOperation pp (p);

	cout << "callbackSendOperation" << endl;

	cout << "Incomming Target : " << pp.getTarget() << endl;


	return 1;
}

int callbackSendChunk (Packet& p)
{
	PacketSendChunk pp (p);

	cout << "callbackSendChunk" << endl;

/*
	Chunk tmp2 = pp.getChunk();

    if(tmp2.isIntegrate())
    {
        cible->saveChunk(tmp2);
    }
    else
    {
        cout<<"le CRC ne correspond pas!!"<<endl;
    }
*/
	return 1;
}

int callbackReady (Packet& p)
{
	PacketReady pp (p);
	
	cout << "callbackIsReady" << endl;
	
	return 1;
}

int callbackChunkReceived (Packet& p)
{
	PacketChunkReceived pp (p);
		
	cout << "callbackChunkReceived" << endl;
	
	return 1;
}

int callbackMd5Error (Packet& p)
{
	PacketMd5Error pp (p);
	
	cout << "callbackMd5Error" << endl;
	
	return 1;
}




