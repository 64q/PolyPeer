#ifndef WAITINGPACKETS_H
#define WAITINGPACKETS_H

#include <list>

#include <Packet.hpp>




class WaitingPackets
{
	private:
		list<Packet> packets;

	public:

		void push(char* data, int size);
		Packet get();
		bool empty();



};

#endif
