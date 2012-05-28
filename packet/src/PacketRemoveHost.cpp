
// Class header
#include <PacketRemoveHost.hpp>

// STL
#include <iostream>
#include <string>

// Project header
#include <Chunk.hpp>

using namespace std;

PacketRemoveHost::PacketRemoveHost(string ip) : Packet()
{
	setType (ERemoveHost);

	(*this) << ip;

}

PacketRemoveHost::PacketRemoveHost(const Packet& p) : Packet(p)
{

}

PacketRemoveHost::~PacketRemoveHost()
{

}

string PacketRemoveHost::getIpAddress ()
{
	setPosition (0);
	string chaine;
	(*this) >> chaine;
	return chaine;
}

