// Class header
#include <PacketSendOperation.hpp>

// STL
#include <iostream>
#include <string>

// Project header
#include <Chunk.hpp>

using namespace std;

PacketSendOperation::PacketSendOperation(string target, int idFile, int numChunk) : Packet()
{
	setType (ESendOperation);

	(*this) << target;
	(*this) << idFile;
	(*this) << numChunk;
}

PacketSendOperation::PacketSendOperation(const Packet& p) : Packet(p)
{

}

PacketSendOperation::~PacketSendOperation()
{

}

string PacketSendOperation::getTarget ()
{
	setPosition (0);
	string chaine;
	(*this) >> chaine;
	return chaine;
}

int PacketSendOperation::getIdFile ()
{
	setPosition (1);
	int idFile;
	(*this) >> idFile;
	return idFile;
}

int PacketSendOperation::getNumChunk ()
{
	setPosition (2);
	int numChunk;
	(*this) >> numChunk;
	return numChunk;
}
