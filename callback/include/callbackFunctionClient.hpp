#ifndef CALLBACKFUNCTION_H
#define CALLBACKFUNCTION_H


/*
 * listes des fonctions de callback
 *
 * par Olivier
 */

// forward declaration
class Packet;

int callbackSendOperation(Packet& p);

int callbackSendChunk(Packet& p);





#endif // CALLBACKFUNCTION_H

