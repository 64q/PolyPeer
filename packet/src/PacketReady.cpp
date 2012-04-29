#include "../include/PacketReady.hpp"


PacketReady::PacketReady() : Packet()
{
	setType (areYouReady);
}

PacketReady::PacketReady(const Packet& p) : Packet(p)
{

}

PacketReady::~PacketReady()
{

}
