#ifndef PACKETREADY_H
#define PACKETREADY_H


/*
 * Classe PacketReady
 *
 * Hérite de la classe Packet
 * Gérer un type de packet spécifique
 *
 *
 *
 *
 * par Olivier
 */


// Project header
#include <Packet.hpp>

class PacketReady : public Packet
{
private:
	

public:
	/**
	* Création d'un PacketReady pret à être envoyé
	* 
	*/
	PacketReady(int idFile, int numChunk);
	
	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketReady(const Packet& p);
	
	/**
	* Destructeur
	*/
	virtual ~PacketReady();
	
	int getIdFile ();

	int getChunkNumber ();
	

private:
	PacketReady() {}

};

#endif // PACKETREADY_H
