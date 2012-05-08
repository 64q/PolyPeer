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
#include <includePacket.hpp>

using namespace std;

int callbackAreYouReady (Packet& p);

int callbackSendOperation (Packet& p);

int callbackSendChunk (Packet& p);

int callbackReady (Packet& p);

int callbackChunkReceived (Packet& p);

int callbackMd5Error (Packet& p);

int callbackNewFile (Packet& p);


#endif // CALLBACKFUNCTION_H

