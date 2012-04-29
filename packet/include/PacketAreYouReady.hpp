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

#include <Packet.hpp>
#include <Data.hpp>

using namespace std;

class PacketAreYouReady : public Packet
{
private:

public:
	/**
	* Constructeur de Packet
	*/
	PacketAreYouReady(int idFile);
	
	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketAreYouReady(const Packet& p);
	
	
	/**
	* Destructeur de Data
	*/
	virtual ~PacketAreYouReady();
	
	
	int getIdFile ();

private:
	PacketAreYouReady() {}

};

#endif // PACKETAREYOUREADY_H
