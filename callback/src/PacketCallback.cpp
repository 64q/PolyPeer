// Class header
#include <PacketCallback.hpp>

// STL
#include <iostream>


using namespace std;

PacketCallback* PacketCallback::instance = 0;

PacketCallback::PacketCallback()
{
	listOperations.resize(int(End_PaquetType), NULL);
}

void PacketCallback::addOperation(PacketType type, pOperation pOp)
{
	if(int(type) > int(EUndefined) && int(type) < int(End_PaquetType))
	{
		listOperations[int(type)] = pOp;
	}
}


int PacketCallback::packetOperation(Packet& p)
{
	if(p.isValid())
	{
		int type = p.getType();
		if(type > int(EUndefined) && type < int(End_PaquetType))
		{
			if(listOperations[type] != NULL)
				return listOperations[type](p);
		}
	}
	else
	{
		if(listOperations[EPacketInvalid] != NULL)
				return listOperations[EPacketInvalid](p);
	}

	return -1;
}

