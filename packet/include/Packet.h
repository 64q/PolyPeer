#ifndef PACKET_H
#define PACKET_H


/*
 * Classe Packet
 *
 * Permet de stocker le contenu d'un paquet
 * Sérialiser un paquet pour l'envoi par socket
 * Création d'un paquet
 * Création de paquet pour le WOL
 *
 * Sécurité :
 * pas de plantage possible sur un mauvais paquet
 *
 * ToDo :
 * vérifier que le paquet est bien destiné à l'application
 *
 * par Olivier
 */

 /* PROTOCOLE
  *
  * structure d'un paquet : (sauf pour le WOL)
  *
  * taille du paquet    -> 4 octets
  * type du paquet      -> 1 octet
  * data du paquet      -> 0 à n octets selon le type
  *
  *
  *
  */


// Entêtes
#include <iostream>
#include <stdint.h>	// pour les types spéciaux
#include <cstring>
#include <string>

#include "Data.h"	// pour gérer le conteneur

using namespace std;

// liste des différents types de paquets
typedef enum
{
    undefined = 0,
    wakeUp,
    areYouReady,
    sendOperation,
    sendChunk,
    readyToWoark,
    chunkReceived,
    error,
} ETypePacket;


// liste des erreurs possibles (pour le protocol)
typedef enum
{
    none,
    addrMacError,
} ETypeError;


class Packet
{
    private:
        // adresse de destination
        string destination;
        // type du paquet
        ETypePacket type;
        // contenu du paquet
        Data data;


    public:
        Packet() : destination(""), type (undefined), data() {}
        virtual ~Packet();


        Packet(char* packet, unsigned int size);

    // changer le contenu ou ajouter des infos
        void setDestination (string dest);


    // Récupérer le contenu
        unsigned int getSize () const;
        void getChar (char* packet) const;
        ETypePacket getType () const;
        string getDestination () const;

    // Création de paquet
        // paquet spécial
        void create_wakeUp (string addrMac);

        // paquets du serveur
        void create_areYouReady (string dest);
        void create_sendOperation (string dest, string secondDest, void * chunk);

        // paquets serveur et client
        void create_sendChunk (string dest, void* chunk);

        // paquets client (réponse)
        void create_readyToWork (string dest);
        void create_chunkReceived (string dest);
        void create_error (unsigned int numError);

    private:
        // reserver de la place dans le
        void allocData (unsigned int size);
        // récupérer le code hexa d'un caractere
        uint32_t charToHexa (char c);

    // remplir correctement un paquet
        void protocol_writeSize (unsigned int size);
        void protocol_writeAddr (string addr, int position);
        void protocol_writeType (ETypePacket type);
        void protocol_writeChunkNbr (uint32_t number, int position);
        void protocol_writeData (char* data, int size, int position);
    // lire correctement un paquet
        void protocol_extrat ();


};

#endif // PACKET_H
