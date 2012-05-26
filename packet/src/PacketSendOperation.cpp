// Class header
#include <PacketSendOperation.hpp>

// STL
#include <iostream>
#include <string>

// Project header
#include <Chunk.hpp>

using namespace std;

PacketSendOperation::PacketSendOperation(string target, Chunk& chunk) : Packet()
{
	setType (ESendOperation);

	(*this) << target;
	(*this) << chunk.serialize();
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

Chunk PacketSendOperation::getChunk ()
{
	setPosition (0);
	Data d;
	(*this) >> d;
	return Chunk(d);
}
