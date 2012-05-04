#include <WaitingPackets.hpp>





void WaitingPackets::push(char* data, int size)
{
	//ajouter la synchro
	packets.push_back(Packet(data, size));
}

Packet WaitingPackets::get()
{
	//ajouter la synchro

	//on récupère le premier packet
	Packet tmp = packets.front();

	//on le supprime de la liste
	packets.pop_front();
	return tmp;
}

bool WaitingPackets::empty()
{
	return packets.empty();
}
