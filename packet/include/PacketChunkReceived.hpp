#ifndef PACKETCHUNKRECEIVED_H
#define PACKETCHUNKRECEIVED_H


/*
 * Classe PacketChunkReceived
 *
 * Hérite de la classe Packet
 * Gérer un type de packet spécifique
 *
 *
 *
 *
 * par Olivier
 */


// Entêtes
#include <iostream>
#include <string>

#include <Packet.hpp>

using namespace std;

class PacketChunkReceived : public Packet
{
private:
	

public:
	/**
	* Création d'un PacketChunkReceived pret à être envoyé
	* 
	*/
	PacketChunkReceived(int idFile, int numChunk);
	
	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketChunkReceived(const Packet& p);
	
	/**
	* Destructeur
	*/
	virtual ~PacketChunkReceived();
	
	int getIdFile ();

	int getChunkNumber ();

private:
	PacketChunkReceived() {}

};

#endif // PACKETCHUNKRECEIVED_H
