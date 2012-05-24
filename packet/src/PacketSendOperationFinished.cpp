// Class header
#include <PacketSendOperationFinished.hpp>

// STL
#include <iostream>


using namespace std;

PacketSendOperationFinished::PacketSendOperationFinished() : Packet()
{
	setType (ESendOperationFinished);
}

PacketSendOperationFinished::PacketSendOperationFinished(const Packet& p) : Packet(p)
{
	
}

PacketSendOperationFinished::~PacketSendOperationFinished()
{
	
}

