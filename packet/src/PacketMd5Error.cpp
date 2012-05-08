#include <PacketMd5Error.hpp>


PacketMd5Error::PacketMd5Error(int idFile, int numChunk) : Packet()
{
	setType (EMd5Error);
	
	(*this) << idFile;
	(*this) << numChunk;
}

PacketMd5Error::PacketMd5Error(const Packet& p) : Packet(p)
{

}

PacketMd5Error::~PacketMd5Error()
{

}

int PacketMd5Error::getIdFile ()
{
	setPosition (0);
	int id;
	(*this) >> id;
	return id;
}

int PacketMd5Error::getChunkNumber ()
{
	setPosition (1);
	int num;
	(*this) >> num;
	return num;
}
