// Class header
#include <PacketDiskFull.hpp>

// STL
#include <iostream>

using namespace std;

PacketDiskFull::PacketDiskFull(int idFile) : Packet()
{
	setType (EDiskFull);
	(*this) << idFile;
}

PacketDiskFull::PacketDiskFull(const Packet& p) : Packet(p)
{
	
}

PacketDiskFull::~PacketDiskFull()
{
	
}

int PacketDiskFull::getIdFile ()
{
	setPosition (0);
	int id;
	(*this) >> id;
	return id;
}
