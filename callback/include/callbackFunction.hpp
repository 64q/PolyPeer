#ifndef CALLBACKFUNCTION_H
#define CALLBACKFUNCTION_H


/*
 * listes des fonctions de callback
 *
 * par Olivier
 */

// Entêtes
#include <iostream>
#include <Packet.hpp>
#include <PacketSendChunk.hpp>
#include <includePacket.hpp>
#include <ServerData.hpp>

using namespace std;

int callbackSendOperation (Packet& p);

int callbackSendChunk (Packet& p);

int callbackReady (Packet& p);

int callbackChunkReceived (Packet& p);

int callbackMd5Error (Packet& p);

int callbackNewFile (Packet& p);

int callbackPacketDiskFull (Packet& p);

int callbackPacketSendOperationFinished (Packet& p);



#endif // CALLBACKFUNCTION_H

