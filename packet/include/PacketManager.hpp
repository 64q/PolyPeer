#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H


/*
 * Classe PacketFactory
 *
 * Permet de construire un paquet à partir de règles
 * 	Création d'un paquet
 * 	Création de paquet pour le WOL
 * Lecture d'un paquet et application de l'opération associée
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
  */


// Entêtes
#include <iostream>
#include <vector>
#include <Chunk.hpp>

#include "Packet.hpp"	// pour gérer le conteneur

using namespace std;

// pointeur sur les opérations



// liste des différents types de paquets
typedef enum
{
    undefined = 0,
    wakeUp,
    areYouReady,
    sendOperation,
    sendChunk,
    readyToWork,
    chunkReceived,
    md5Error,
    
    End_PaquetType, // Doit rester en derniere position, pour avoir la taille du tableau
} PacketType;

typedef int (*pOperation) (Packet& p);

class PacketManager
{
private:
	static PacketManager* instance;

	PacketManager()	{ listOperations.resize ( int (End_PaquetType), NULL); }
	PacketManager(const PacketManager& pm)	{ }
	
	vector<pOperation> listOperations;
    
	
public:
	static PacketManager* getPacketManager()
	{
		if (PacketManager::instance == NULL)
			PacketManager::instance = new PacketManager();
		return PacketManager::instance;
	}

	static void quit()
	{
		if (PacketManager::instance != NULL)
		{
			delete PacketManager::instance;
			PacketManager::instance = NULL;
		}
	}
	
	void addOperation (PacketType type, pOperation);

// Création de paquet
    // paquets du serveur
    Packet newPacket_areYouReady ();
    Packet newPacket_sendOperation (string secondDest, Chunk& chunk);

    // paquets serveur et client
    Packet newPacket_sendChunk (string dest, Chunk& chunk);

    // paquets client (réponse)
    Packet newPacket_readyToWork ();
    Packet newPacket_chunkReceived (int idFile, int numChunk);
    Packet newPacket_md5Error (int idFile);

// Lecture et interprétation du paquet
	int packetOperation (Packet& p);

};

#endif // PACKETMANAGER_H

