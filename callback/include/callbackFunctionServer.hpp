#ifndef CALLBACKFUNCTION_H
#define CALLBACKFUNCTION_H


/*
 * listes des fonctions de callback
 *
 * par Olivier
 */

// forward declaration
class Packet;

int callbackReady(Packet& p);

int callbackChunkReceived(Packet& p);

int callbackMd5Error(Packet& p);

int callbackNewFile(Packet& p);

int callbackPacketDiskFull(Packet& p);

int callbackPacketSendOperationFinished(Packet& p);

int callBackAddHost(Packet& p);

int callbackRemoveHost(Packet& p);



#endif // CALLBACKFUNCTION_H

