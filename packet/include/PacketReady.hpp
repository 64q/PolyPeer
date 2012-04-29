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


// Entêtes
#include <iostream>

#include "Packet.hpp"

using namespace std;

class PacketReady : public Packet
{
private:
	

public:
	/**
	* Création d'un PacketReady pret à être envoyé
	* 
	*/
	PacketReady();
	
	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketReady(const Packet& p);
	
	/**
	* Destructeur
	*/
	virtual ~PacketReady();
	
	

private:


};

#endif // PACKETREADY_H
