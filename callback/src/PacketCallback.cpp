#include <PacketCallback.hpp>

PacketCallback* PacketCallback::instance = 0;

PacketCallback::PacketCallback()	
{ 
	listOperations.resize ( int (End_PaquetType), NULL);
	
	// Configuration des callback
	this->addOperation (ENewFile, callbackNewFile);
	this->addOperation (ESendOperation, callbackSendOperation);
	this->addOperation (ESendChunk, callbackSendChunk);
	this->addOperation (EReady, callbackReady);
	this->addOperation (EChunkReceived, callbackChunkReceived);
	this->addOperation (EMd5Error, callbackMd5Error);
	this->addOperation (EDiskFull, callbackPacketDiskFull);
	this->addOperation (ESendOperationFinished, callbackPacketSendOperationFinished);
	
}

void PacketCallback::addOperation (PacketType type, pOperation pOp)
{
	if ( int(type) > int(EUndefined) && int(type) < int(End_PaquetType))
	{
		listOperations[int(type)] = pOp;
	}
}


int PacketCallback::packetOperation (Packet& p)
{
	int type = p.getType();
	if ( type > int(EUndefined) && type < int(End_PaquetType))
	{
		if (listOperations[type] != NULL)
			return listOperations[type](p);
	}
	return -1;
}

