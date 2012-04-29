#include "../include/PacketAreYouReady.hpp"


PacketAreYouReady::PacketAreYouReady(string m) : Packet()
{
	setType (areYouReady);
	
	msg = m;	
	
	(*this) << msg;
}

PacketAreYouReady::PacketAreYouReady(const Packet& p) : Packet(p)
{
	(*this) >> msg;
}

PacketAreYouReady::~PacketAreYouReady()
{

}

string PacketAreYouReady::getMessage ()
{
	return msg;
}
