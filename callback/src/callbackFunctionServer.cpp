#include <callbackFunction.hpp>
using namespace std;

int callbackReady (Packet& p)
{
	PacketReady pp (p);

	cout << "callbackIsReady" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost (src, pp.getIdFile(), pp.getChunkNumber());

	return 1;
}

int callbackChunkReceived (Packet& p)
{
	PacketChunkReceived pp (p);

	cout << "callbackChunkReceived" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost(src, pp.getIdFile(), pp.getChunkNumber());

	return 1;
}

int callbackMd5Error (Packet& p)
{
	PacketMd5Error pp (p);

	cout << "callbackMd5Error" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost(src, pp.getIdFile(), WAIT);

	return 1;
}

int callbackPacketDiskFull (Packet& p)
{
	PacketDiskFull pp (p);

	cout << "callbackPacketDiskFull5Error" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost(src, pp.getIdFile(), FULL);

	return 1;
}

int callbackPacketSendOperationFinished (Packet& p)
{
	PacketSendOperationFinished pp (p);

	cout << "callbackPacketSendOperationFinished" << endl;

	ServerData* sd = ServerData::getInstance();

	string src = p.getAddress();

	sd->updateHost(src, WAIT);

	return 1;
}




