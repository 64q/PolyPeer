#include <iostream>

#include <FileManager.hpp>
#include <Chunk.hpp>
#include <md5.hpp>

#include <Data.hpp>
#include <Packet.hpp>
#include <PacketCallback.hpp>
#include <includePacket.hpp>




using namespace std;


// contenu dans la structure globale du prog
char file1[] = "vid.flv";
char file2[] = "output.flv";
FileManager* cible;





int main ()
{

// Création du manager
	PacketCallback* pm = PacketCallback::getPacketCallback ();
	

/*
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
*/
// Destruction du manager
	PacketCallback::quit ();

	return 0;
}


