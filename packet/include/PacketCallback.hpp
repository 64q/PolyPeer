#ifndef PACKETCALLBACK_H
#define PACKETCALLBACK_H


/*
 * Classe PacketCallback
 *
 *
 * Associer un callback pour traiter un paquet
 *
 * par Olivier
 */


// Entêtes
#include <iostream>
#include <vector>


#include <Packet.hpp>	// pour gérer le conteneur
#include <callbackFunction.hpp>

using namespace std;


/**
 * Definition du type des fonctions de callback
 */
typedef int (*pOperation) (Packet& p);


class PacketCallback
{
private:
	/**
	 * Pour avoir une classe en mode singleton
	 */
	static PacketCallback* instance;
	
	/**
	 * Redefinition des constructeur en privé pour empecher l'instanciation de la classe
	 */
	PacketCallback();
	PacketCallback(const PacketCallback& pm)	{ }
	
	/**
	 * liste des fonctions de callback
	 */
	vector<pOperation> listOperations;
    
	
public:
	/**
	 * Fonction de Classe
	 * Récupérer l'instance de la classe
	 */
	static PacketCallback* getPacketCallback()
	{
		if (PacketCallback::instance == NULL)
			PacketCallback::instance = new PacketCallback();
		return PacketCallback::instance;
	}
	
	/**
	 * Fonction de classe
	 * Détruire l'instance de la classe
	 */
	static void quit()
	{
		if (PacketCallback::instance != NULL)
		{
			delete PacketCallback::instance;
			PacketCallback::instance = NULL;
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


};

#endif // PACKETCALLBACK_H

