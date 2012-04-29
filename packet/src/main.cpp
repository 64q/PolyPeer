#include <iostream>


/*

#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
*/

#include <Data.hpp>
#include <Packet.hpp>
#include <PacketAreYouReady.hpp>
#include <PacketCallback.hpp>

using namespace std;

int callbackAreYouReady (Packet& p)
{
	PacketAreYouReady pp(p);
	
	cout << pp.getIdFile() << endl;
	
	return 1;
}


int main ()
{
	// Création du manager
	PacketCallback* pm = PacketCallback::getPacketCallback ();
	// Configuration des callback
	pm->addOperation (areYouReady, callbackAreYouReady);
	
	// création d'un paquet
	PacketAreYouReady payr = PacketAreYouReady (5);
	
	
	
	// Analyse du paquet
	pm->packetOperation (payr);
	
	// Destruction du manager
	PacketCallback::quit ();
	
	
	
	
	
	
	return 0;
}


