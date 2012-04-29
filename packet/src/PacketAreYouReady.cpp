#include <PacketAreYouReady.hpp>


PacketAreYouReady::PacketAreYouReady(int idFile) : Packet()
{
	setType (areYouReady);
	
	(*this) << idFile;
}

PacketAreYouReady::PacketAreYouReady(const Packet& p) : Packet(p)
{
	
}

PacketAreYouReady::~PacketAreYouReady()
{
	
}

int PacketAreYouReady::getIdFile ()
{
	setPosition (0);
	int id;
	(*this) >> id;
	return id;
}
