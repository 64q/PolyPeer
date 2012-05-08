#include <iostream>
#include <ServerSocket.hpp>
#include <ConnectionManager.hpp>
#include <FileManager.hpp>


#include <PacketNewFile.hpp>
#include <PacketSendChunk.hpp>
#include <PacketChunkReceived.hpp>
using namespace std;

int main()
{

	ConnectionManager cm;
	cm.start();

	for(;;);
/*

	try
	{
		//lancement du serveur
		ServerSocket server(5555);


		//initialisation de le liste d'attente des messages
		WaitingPackets wp;
		ConnectionManager cm(&wp);

		//initialisation du gestionnaire de fichier
		FileManager fm("Super 8.avi",0, 10000, 6546);
	cout << "il ya "<<fm.getNumberChunk()<<" Chunk(s) à envoyer!"<<endl;

	cout << "serveur en attente" << endl;
		Socket* sock = server.accept();

		//on ajoute la connection reçu au connection manager (le  nom est arbitraire)
		cm.addConnection("IRC009-11",sock);
	cout << "client ajoute" << endl;

		//on lui envoie le paquet d'initalisation de l'envoie de fichier
		Packet* packet = new PacketNewFile(fm.getIdFile(), fm.getFileName(), fm.getFileSize(), fm.getChunkSize());
	cout << "packet pret a l'envoi" << endl;

		//envoie du paquet (voir si on ajoute une méthode d'envoie plus concise)
		cm.getConnection("IRC009-11")->getSocket()->send(packet->serialize().c_str(), packet->serialize().getSize());
	cout << "premier packet recu" << endl;
		delete packet;

		//tant que la liste est vide, on a pas reçu de message (ne sera pas utiliser comme ça)
		while(wp.empty());



	cout << "un truc a ete recu" << endl;
		//si le paquet reçu est de type Ready on lance l'envoi
		if(wp.get().getType() == isReady)
		{
		cout << "le client est pret" << endl;
			int i =0;
			int currentChunk = 0;

			while(i < fm.getNumberChunk() && i == currentChunk)
			{
			cout << "le chunk " << i << " va etre envoye" << endl;

				Chunk chunk = fm.getChunk(i);
			cout << "chunk charge" << endl;
				packet = new PacketSendChunk(chunk );
			cout << "paquet pret" << endl;
				cm.getConnection("IRC009-11")->getSocket()->send(packet->serialize().c_str(), packet->serialize().getSize());
				delete packet;
			cout << "le chunk a ete envoye " << endl;

				while(wp.empty());
				Packet packetReceived = wp.get();
				if(packetReceived.getType()==chunkReceived)
				{

					PacketChunkReceived* packetChunk = new PacketChunkReceived(packetReceived);
					currentChunk = packetChunk->getChunkNumber() + 1;
					delete packetChunk;

				}
				i++;

			}
			cout << "transmission terminée" << endl;
		}else
		{
			cout << "problème du client: pas prêt" << endl;
		}

	}catch(ConnectionException)
	{
		cout << "erreur à la connection" << endl;
	}



*/


}
