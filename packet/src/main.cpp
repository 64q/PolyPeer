#include <iostream>


#include <Data.hpp>
#include <Packet.hpp>
#include <PacketAreYouReady.hpp>
#include <PacketSendOperation.hpp>
#include <PacketMd5Error.hpp>

#include <PacketCallback.hpp>

#include <Chunk.hpp>

using namespace std;

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


int main ()
{
	// Création du manager
	PacketCallback* pm = PacketCallback::getPacketCallback ();
	// Configuration des callback
	pm->addOperation (areYouReady, callbackAreYouReady);
	pm->addOperation (sendOperation, callbackSendOperation);
	
	// création d'un paquet
	//Packet p = PacketAreYouReady (5);
	Packet p = PacketMd5Error(5, 14545);
	
	// préparation envoie
	Data d = p.serialize ();
	
	cout << "taille du packet : " << d.getSize () << endl;
	cout << "Contenu du packet : " << d.getString () << endl;
	
	//reception
	Packet pp(d);
	
	// Analyse du paquet
	pm->packetOperation (pp);
	
	// Destruction du manager
	PacketCallback::quit ();
	
	
	
	
	
	
	return 0;
}


