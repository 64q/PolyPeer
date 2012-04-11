#include "../include/Packet.h"


Packet::Packet(char* packet, unsigned int size) : destination(""), type (undefined), data(""), error(none)
{
    data.reserve (size);
    for (unsigned int i =0;i < size; i++)
        data += packet[i];
}

void Packet::setDestination (string dest)
{
    destination = dest;
}

unsigned int Packet::getSize () const
{
    return data.size();
}

void Packet::getChar (char* packet) const
{
    // vérif de l'allocation
    if (packet != 0)
        return;

    // copie dans le conteneur c
    strcpy (packet, data.c_str());
}

ETypePacket Packet::getType () const
{
    return type;
}

string Packet::getDestination () const
{
    return destination;
}

void Packet::create_wakeUp (string addrMac)
{
    data.resize (0);
    if (addrMac.size () == 17)
    {
        error = none;
        type = wakeUp;
        // pour tout le réseau
        destination = "255.255.255.255";

    // 6 octets a 0xFF et 16 * 6 octets d'adresse MAC
        // les 6 premiers octets sont remplis avec 0xFF
        for (int i = 0; i < 6; i++)
            data += 0xFF;

        // les octets suivants sont remplis avec @MAC répété 16 fois
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 6; j++)
                data += ((charToHexa(addrMac.at(i*6 +j*3)) << 4) || charToHexa(addrMac.at(i*17 +j*3+1)));
        }
    }
    else
    {
        error = addrMacError;
    }
}

void Packet::create_areYouReady (string dest)
{
    // definition des valeurs pour ce type
    error = none;
    type = areYouReady;
    destination = dest;
    // taille : 4o, type : 1o = 5o

    // remplissage du paquet
    protocol_writeSize(data.size());
    protocol_writeType (type);
}

void Packet::create_sendOperation (string dest, string secondDest, void * chunk)
{
    // definition des valeurs pour ce type
    error = none;
    type = sendOperation;
    destination = dest;
    //size = 4 + 1 + 4 + 15;

    // remplissage du paquet
    protocol_writeSize(data.size());   // pos 0
    protocol_writeType (type);  // pos 4
    //protocol_writeChunkInfo (chunkNumber, 5); // pos 5
    protocol_writeAddr (secondDest, 9); // pos 9

}

void Packet::create_sendChunk (string dest, void* chunk)
{
    // definition des valeurs pour ce type
    error = none;
    type = sendChunk;
    destination = dest;
    //size = 4 + 1;
    //size += chunk.size ();

    // remplissage du paquet
    protocol_writeSize(data.size());
    protocol_writeType (type);
    //protocol_writeData (char* data, int size, int position)
}

void Packet::create_readyToWork (string dest)
{
    // definition des valeurs pour ce type
    error = none;
    type = sendOperation;
    destination = dest;
    //size = 4 + 1 + 4;

    // remplissage du paquet
    protocol_writeSize(data.size());   // pos 0
    protocol_writeType (type);  // pos 4
    //protocol_writeChunkNbr (chunkNumber, 5); // pos 5
    //protocol_writeAddr (secondDest, 9); // pos 9

}

void Packet::create_chunkReceived (string dest)
{

}

void Packet::create_error (unsigned int numError)
{

}


uint32_t Packet::charToHexa (char c)
{
    int toReturn = int(c) - int ('0');
    if (toReturn < 0 || toReturn > 15)
        toReturn = 0;
    return toReturn;
}

void Packet::protocol_writeSize (unsigned int size)
{
/*
    if (data != 0)
    {
        uint32_t mySize = size;
        data[0] = (mySize >> 24);
        data[1] = ((mySize >> 16) && 0x000000FF);
        data[2] = ((mySize >> 8) && 0x000000FF);
        data[3] = (mySize && 0x000000FF);
    }*/
}

void Packet::protocol_writeType (ETypePacket type)
{
 /*   if (data != 0)
    {
        data[4] = uint8_t (type);
    }*/
}

void Packet::protocol_writeAddr (string addr, int position)
{
 /*   if (data != 0 && addr.size() == 15)
    {
        for (int i = 0; i < 15)
        {
            data[i+position] = addr.at(i);
        }
    }*/
}

void Packet::protocol_writeChunkNbr (uint32_t number, int position)
{
 /*   if (data != 0)
    {
        for (int i = 0; i < 15)
        {
            data[position+0] = (number >> 24);
            data[position+1] = ((number >> 16) && 0x000000FF);
            data[position+2] = ((number >> 8) && 0x000000FF);
            data[position+3] = (number && 0x000000FF);
        }
    }*/
}

void Packet::protocol_writeData (char* data, int size, int position)
{
 /*   if (data != 0)
    {
        for (int i = 0; i < size; i++)
        {
            this->data[position+i] = data [i];
        }
    }*/
}



