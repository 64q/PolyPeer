#ifndef PACKETAREYOUREADY_H
#define PACKETAREYOUREADY_H


/*
 * Classe PacketAreYouReady
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

#include "Packet.hpp"

using namespace std;

class PacketAreYouReady : public Packet
{
private:
	string msg;

public:
	/**
	* Constructeur de Packet
	*/
	PacketAreYouReady(string m);
	
	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketAreYouReady(const Packet& p);
	
	
	/**
	* Destructeur de Data
	*/
	virtual ~PacketAreYouReady();
	
	
	string getMessage ();

private:


};

#endif // PACKETAREYOUREADY_H
