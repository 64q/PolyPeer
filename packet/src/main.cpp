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
#include "../include/PacketManager.hpp"


using namespace std;

int maFonction (Packet& p)
{
	cout << " operation areYouReady " << endl;
	
	string tmp;
	p >> tmp;
	cout << "val : " << tmp << endl;
	p >> tmp;
	cout << "val : " << tmp << endl;
	return 0;
}


int main ()
{
	PacketManager* pm = PacketManager::getPacketManager ();

	pm->addOperation (areYouReady, maFonction);

	Packet p2 =	pm->newPacket_areYouReady ();
	
	pm->packetOperation (p2);
	
	PacketManager::quit ();
	
	return 0;
}


