#include <PacketChunkReceived.hpp>


PacketChunkReceived::PacketChunkReceived(int idFile, int numChunk) : Packet()
{
	setType (chunkReceived);
	
	(*this) << idFile;
	(*this) << numChunk;
}

PacketChunkReceived::PacketChunkReceived(const Packet& p) : Packet(p)
{

}

PacketChunkReceived::~PacketChunkReceived()
{

}

int PacketChunkReceived::getIdFile ()
{
	setPosition (0);
	int id;
	(*this) >> id;
	return id;
}

int PacketChunkReceived::getChunkNumber ()
{
	setPosition (1);
	int num;
	(*this) >> num;
	return num;
}
