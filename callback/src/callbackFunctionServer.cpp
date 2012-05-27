// Class header
#include <callbackFunctionServer.hpp>

// STL
#include <iostream>

// Project header
#include <PolypeerServer.hpp>
#include <ServerData.hpp>
#include <Packet.hpp>
#include <includePacket.hpp>


using namespace std;

int callbackReady(Packet& p)
{
	PacketReady pp (p);

	cout << "callbackReady" << endl;

	ServerData& sd = PolypeerServer::getInstance()->getServerData();

	string src = p.getAddress();

	sd.updateHost (src, pp.getIdFile(), pp.getChunkNumber());

	return 1;
}

int callbackChunkReceived(Packet& p)
{
	PacketChunkReceived pp (p);

	cout << "callbackChunkReceived" << endl;

	ServerData& sd = PolypeerServer::getInstance()->getServerData();

	string src = p.getAddress();

	sd.updateHost(src, pp.getIdFile(), pp.getChunkNumber());

	return 1;
}

int callbackMd5Error(Packet& p)
{
	PacketMd5Error pp (p);

	cout << "callbackMd5Error" << endl;

	ServerData& sd = PolypeerServer::getInstance()->getServerData();

	string src = p.getAddress();

	sd.updateHost(src, WAIT);

	return 1;
}

int callbackPacketDiskFull(Packet& p)
{
	PacketDiskFull pp (p);

	cout << "callbackPacketDiskFull5Error" << endl;

	ServerData& sd = PolypeerServer::getInstance()->getServerData();

	string src = p.getAddress();

	sd.updateHost(src, FULL);

	return 1;
}

int callbackPacketSendOperationFinished(Packet& p)
{
	PacketSendOperationFinished pp (p);

	cout << "callbackPacketSendOperationFinished" << endl;

	ServerData& sd = PolypeerServer::getInstance()->getServerData();

	string src = p.getAddress();

	sd.updateHost(src, WAIT);

	return 1;
}

int callBackAddHost(Packet& p)
{
	PacketAddHost pp (p);
	
	cout << "PacketAddHost" << endl;
	
	ServerData& sd = PolypeerServer::getInstance()->getServerData();

	sd.updateHost(pp.getIpAddress(), WAIT);
	
	return 1;
}



