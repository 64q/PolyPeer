#ifndef PACKETMD5ERROR_H
#define PACKETMD5ERROR_H


/*
 * Classe PacketMd5Error
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


class PacketMd5Error : public Packet
{
private:


public:
	/**
	* Création d'un PacketMd5Error pret à être envoyé
	* 
	*/
	PacketMd5Error(int idFile, int numChunk);
	
	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketMd5Error(const Packet& p);
	
	/**
	* Destructeur
	*/
	virtual ~PacketMd5Error();
	
	
	int getIdFile ();
	
	int getChunkNumber ();
	

private:
	/**
	* 
	*/
	PacketMd5Error() {}

};

#endif // PACKETMD5ERROR_H
