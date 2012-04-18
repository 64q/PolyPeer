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
  * Voir les descriptifs de fonction
  *
  */


// Entêtes
#include <iostream>
#include <vector>
#include <Chunk.hpp>

#include "Packet.hpp"	// pour gérer le conteneur

using namespace std;


/**
 * liste des différents types de paquets
 */
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

/**
 * Definition du type des fonctions de callback
 */
typedef int (*pOperation) (Packet& p);


class PacketManager
{
private:
	/**
	 * Pour avoir une classe en mode singleton
	 */
	static PacketManager* instance;
	
	/**
	 * Redefinition des constructeur en privé pour empecher l'instanciation de la classe
	 */
	PacketManager()	{ listOperations.resize ( int (End_PaquetType), NULL); }
	PacketManager(const PacketManager& pm)	{ }
	
	/**
	 * liste des fonctions de callback
	 */
	vector<pOperation> listOperations;
    
	
public:
	/**
	 * Fonction de Classe
	 * Récupérer l'instance de la classe
	 */
	static PacketManager* getPacketManager()
	{
		if (PacketManager::instance == NULL)
			PacketManager::instance = new PacketManager();
		return PacketManager::instance;
	}
	
	/**
	 * Fonction de classe
	 * Détruire l'instance de la classe
	 */
	static void quit()
	{
		if (PacketManager::instance != NULL)
		{
			delete PacketManager::instance;
			PacketManager::instance = NULL;
		}
	}
	
	/**
	 * Ajouter la fonction de callback correspondant à un type de paquet
	 * @param PacketType
	 *	type du paquet
	 * @param int (*pOperation) (Packet& p);
	 *  fonction associée
	 */
	void addOperation (PacketType type, pOperation);

	/**
	 * Ajouter la fonction de callback correspondant à un type de paquet
	 * @param Packet&
	 *	paquet à traiter
	 * @return int
	 *  -1 pour un probleme d'appel
	 *  sinon c'est le retour de la fonctiuon associée
	 */
	int packetOperation (Packet& p);

    /**
	 * Création d'un paquet areYouReady
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_areYouReady ();
    
 	/**
	 * Création d'un paquet sendOperation
	 * @param string
	 *	adresse deuxieme PC client qui doit recevoir le chunk
	 * @param chunk
	 *	le contenu du fichier à faire passer
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_sendOperation (string secondDest, Chunk& chunk);

    /**
	 * Création d'un paquet sendChunk
	 * @param chunk
	 *	le contenu du fichier à envoyer
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_sendChunk (Chunk& chunk);

    /**
	 * Création d'un paquet readyToWork
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_readyToWork ();
    
    /**
	 * Création d'un paquet chunkReceived
	 * @param int
	 *	id du fichier qui a été recu
	 * @param int
	 *	chaunk du fichier recu
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_chunkReceived (int idFile, int numChunk);
    
   /**
	 * Création d'un paquet md5Error
	 * @param int
	 *	id du fichier qui a été recu
	 * @param int
	 *	chaunk du fichier recu
	 * @return Packet
	 *	le paquet créé
	 */
    Packet newPacket_md5Error (int idFile, int numChunk);

};

#endif // PACKETMANAGER_H

