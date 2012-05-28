// Class header
#include <PacketAddHost.hpp>

// STL
#include <iostream>
#include <string>


PacketAddHost::PacketAddHost(std::string ipAddress): Packet()
{
	setType (EAddHost);

	(*this) << ipAddress;

}

PacketAddHost::PacketAddHost(const Packet& p) : Packet(p)
{

}

PacketAddHost::~PacketAddHost()
{

}

std::string PacketAddHost::getIpAddress ()
{
	setPosition (0);
	std::string ip;
	(*this) >> ip;
	return ip;
}


