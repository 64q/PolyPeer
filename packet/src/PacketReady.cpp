// Class header
#include <PacketReady.hpp>

// STL
#include <iostream>

using namespace std;

PacketReady::PacketReady(int idFile, int numChunk) : Packet()
{
	setType (EReady);
	
	(*this) << idFile;
	(*this) << numChunk;
}

PacketReady::PacketReady(const Packet& p) : Packet(p)
{

}

PacketReady::~PacketReady()
{

}

int PacketReady::getIdFile ()
{
	setPosition (0);
	int id;
	(*this) >> id;
	return id;
}

int PacketReady::getChunkNumber ()
{
	setPosition (1);
	int num;
	(*this) >> num;
	return num;
}
