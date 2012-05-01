#include <iostream>

#include <FileManager.hpp>
#include <Chunk.hpp>
#include <md5.hpp>

#include <Data.hpp>
#include <Packet.hpp>
#include <PacketAreYouReady.hpp>
#include <PacketSendOperation.hpp>
#include <PacketSendChunk.hpp>
#include <PacketCallback.hpp>



using namespace std;


// contenu dans la structure globale du prog
char file1[] = "a.avi";
char file2[] = "output.avi";
FileManager* cible;




int callbackAreYouReady (Packet& p)
{
	PacketAreYouReady pp(p);

	cout << "Incomming Value : " << pp.getIdFile() << endl;

	return 1;
}

int callbackSendOperation (Packet& p)
{
	PacketSendOperation pp (p);



	cout << "Incomming Target : " << pp.getTarget() << endl;


	return 1;
}

int callbackSendChunk (Packet& p)
{
	PacketSendChunk pp (p);


	Chunk tmp2 = pp.getChunk();

    if(tmp2.isIntegrate())
    {
        cible->saveChunk(tmp2);
    }
    else
    {
        cout<<"le CRC ne correspond pas!!"<<endl;
    }

	return 1;
}


int main ()
{

// Création du manager
	PacketCallback* pm = PacketCallback::getPacketCallback ();
	// Configuration des callback
	pm->addOperation (areYouReady, callbackAreYouReady);
	pm->addOperation (sendOperation, callbackSendOperation);
	pm->addOperation (sendChunk, callbackSendChunk);




// FICHIER

    FileManager fmanager(file1,0, 1000000, 2312);

    cible = new FileManager(file2,fmanager.getFileSize(), 1000000, 2312);


    string tmpStr;



    for(int i=0; i<fmanager.getNumberChunk() ; i++)
    {
        Chunk tmp = fmanager.getChunk(i);

        // création d'un paquet
			//PacketAreYouReady p (5);
			//PacketSendOperation p ("192.168.0.2", Chunk());
			PacketSendChunk p (tmp);

			// préparation envoie
			Data d = p.serialize ();

			//cout << "ENVOI (taille packet : " << d.getSize () << ")" << endl;
			//cout << "Contenu du packet : " << d.getString () << endl;


		//reception
			Packet pp(d);

		// Analyse du paquet
			pm->packetOperation (pp);

    }

    cout << "Nombre de paquets nécessaires : " << fmanager.getNumberChunk() << endl;

// destruction de la cible qui est en variable globale
	//delete cible;

// Destruction du manager
	PacketCallback::quit ();

	return 0;
}


