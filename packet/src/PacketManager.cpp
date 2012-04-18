#include "../include/PacketManager.hpp"

PacketManager* PacketManager::instance = 0;

void PacketManager::addOperation (PacketType type, pOperation pOp)
{
	if ( int(type) > int(undefined) && int(type) < int(End_PaquetType))
	{
		listOperations[int(type)] = pOp;
	}
}

Packet PacketManager::newPacket_areYouReady ()
{
	Packet p;
	p<< int(areYouReady);
	p<<"Bonjour !";
	p<<"ca va ?";
	
	return p;
}


Packet PacketManager::newPacket_sendOperation (string secondDest, Chunk& chunk)
{
	Packet p;
	p<< int(sendOperation);
	
	
	return p;
}

Packet PacketManager::newPacket_sendChunk (string dest, Chunk& chunk)
{
	Packet p;
	p<< int(sendChunk);
	
	
	return p;
}

Packet PacketManager::newPacket_readyToWork ()
{
	Packet p;
	p<< int(readyToWork);
	
	
	return p;
}

Packet PacketManager::newPacket_chunkReceived (int idFile, int numChunk)
{
	Packet p;
	p<< int(chunkReceived);
	p<< idFile;
	p<< numChunk;
	
	return p;
}

Packet PacketManager::newPacket_md5Error (int idFile)
{
	Packet p;
	p<< int(md5Error);
	p<< idFile;
	
	return p;
}

int PacketManager::packetOperation (Packet& p)
{
	int type;
	p.resetPosition ();
	p >> type;
	if ( type > int(undefined) && type < int(End_PaquetType))
	{
		return listOperations[type](p);
	}
	return -1;
}

