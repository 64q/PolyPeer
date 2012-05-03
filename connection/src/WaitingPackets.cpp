#include <WaitingPackets.hpp>





void WaitingPackets::push(char* data, int size)
{

	packets.push_back(Packet(data, size));
}

Packet WaitingPackets::get()
{
	Packet tmp = packets.front();
	packets.pop_front();
	return tmp;
}

bool WaitingPackets::empty()
{
	return packets.empty();
}
