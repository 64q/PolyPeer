#include <iostream>
#include <string>

#include <ServerSocket.hpp>
#include <FileManager.hpp>
#include <TcpExceptions.hpp>
#include <Packet.hpp>
#include <PacketNewFile.hpp>
#include <PacketSendChunk.hpp>
#include <PacketChunkReceived.hpp>
#include <PacketReady.hpp>
using namespace std;

void* start(void* data);

int main()
{



	//connection u serveur

    Socket sock("localhost",5555);
cout << "connecte" << endl;
/*

    char data[100000];

    //on récupère le paquet d'initialisation
    int size = sock.read(data, 100000);
    Packet* packet = new Packet(data, size);
cout << "premier packet recu" << endl;

	//on vérifie que c'est le bon type de paquet
    if(packet->getType() == sendOperation)
    {
	cout << "packet sendOperation reçu" << endl;
    	PacketNewFile* packetNew = new PacketNewFile(*packet);

		//on initialise le FileManager avec les infos reçu dans le paquet
		FileManager fm(packetNew->getFileName().c_str(), packetNew->getFileSize(), packetNew->getChunkSize(), packetNew->getIdFile());
	cout << "filemanager pret" << endl;

		delete packet;

		//on prépare la réponse
		PacketReady* packetReady = new PacketReady(packetNew->getIdFile(), 0);

		sock.send(packetReady->serialize().c_str(), packetReady->serialize().getSize());

		delete packetNew;
		delete packetReady;
	cout << "paquet de lancement envoye au serveur" << endl;

		int i = 0;
		bool run = true;

		//on boucle jusqu'à temps de recevoir tous les Chunks
		while(i < fm.getNumberChunk() && run)
		{
			size = sock.read(data, 100000);
			cout << "paquet recu" << endl;
			packet = new Packet(data, size);
			if(packet->getType() == sendChunk)
			{
				//si le paquet reçu est un paquet de donné Chunk
				PacketSendChunk* packetChunk = new PacketSendChunk(*packet);

				delete packet;
				//on récupère le paquet
				Chunk chunk = packetChunk->getChunk();
				delete packetChunk;
				//on vérifie qu'il est complet
				if(chunk.isIntegrate())
				{
					//on l'enregistre
					fm.saveChunk(chunk);

					//on répond au serveur
					PacketChunkReceived* packetReceived = new PacketChunkReceived(fm.getIdFile(), i);
					sock.send(packetReceived->serialize().c_str(), packetReceived->serialize().getSize());
					delete packetReceived;
				}else
				{
					cout << "chunk corrompu" << endl;
					run = false;
				}

			}else
			{
				run = false;
			}
			i++;
		}


    }
	cout << "fini" << endl;
	system("pause");

    return 0;
*/


}


