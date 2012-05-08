#include <PacketSendOperationFinished.hpp>


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

