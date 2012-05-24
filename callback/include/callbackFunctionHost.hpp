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

#include <Clientdata.hpp>


using namespace std;

int callbackSendOperation (Packet& p);

int callbackSendChunk (Packet& p);





#endif // CALLBACKFUNCTION_H

