#include <iostream>


/*

#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
*/

#include "../include/Data.hpp"
#include "../include/Packet.hpp"
#include "../include/PacketAreYouReady.hpp"
#include "../include/PacketCallback.hpp"

using namespace std;

int callbackAreYouReady (Packet& p)
{
	PacketAreYouReady pp(p);
	
	cout << pp.getMessage() << endl;
	
	return 1;
}


int main ()
{
	// Création du manager
	PacketCallback* pm = PacketCallback::getPacketCallback ();
	// Configuration des callback
	pm->addOperation (areYouReady, callbackAreYouReady);
	
	// création d'un paquet
	PacketAreYouReady payr = PacketAreYouReady ("Salut !");
	
	
	
	// Analyse du paquet
	pm->packetOperation (payr);
	
	// Destruction du manager
	PacketCallback::quit ();
	
	
	
	
	
	
	return 0;
}


