#include <PacketSendChunk.hpp>


PacketSendChunk::PacketSendChunk(Chunk& chunk) : Packet()
{
	setType (sendChunk);

	(*this) << chunk.serialize();
}

PacketSendChunk::PacketSendChunk(const Packet& p) : Packet(p)
{

}

PacketSendChunk::~PacketSendChunk()
{

}

Chunk PacketSendChunk::getChunk ()
{
	setPosition (0);
	Data d;
	(*this) >> d;
	return Chunk(d);
}

