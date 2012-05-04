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
	try
	{
		ServerSocket server(5555);

		WaitingPackets wp;
		ConnectionManager cm(&wp);

		FileManager fm("a.png",0, 10000, 6546);


	cout << "serveur en attente" << endl;
		Socket* sock = server.accept();

		cm.addConnection("IRC009-11",sock);
	cout << "client ajoute" << endl;
		Packet* packet = new PacketNewFile(fm.getIdFile(), fm.getFileName(), fm.getFileSize(), fm.getChunkSize());
	cout << "packet pret a l'envoi" << endl;
		cm.getConnection("IRC009-11")->getSocket()->send(packet->serialize().c_str(), packet->serialize().getSize());
	cout << "premier packet recu" << endl;
		delete packet;

		while(wp.empty());



	cout << "un truc a ete recu" << endl;

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






}
