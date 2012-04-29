#include "../include/PacketCallback.hpp"

PacketCallback* PacketCallback::instance = 0;

void PacketCallback::addOperation (PacketType type, pOperation pOp)
{
	if ( int(type) > int(undefined) && int(type) < int(End_PaquetType))
	{
		listOperations[int(type)] = pOp;
	}
}


int PacketCallback::packetOperation (Packet& p)
{
	int type = p.getType();
	if ( type > int(undefined) && type < int(End_PaquetType))
	{
		if (listOperations[type] != NULL)
			return listOperations[type](p);
	}
	return -1;
}

