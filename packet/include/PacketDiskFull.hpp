#ifndef PacketDiskFull_H
#define PacketDiskFull_H


/*
 * Classe PacketDiskFull
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

class PacketDiskFull : public Packet
{
private:

public:
	/**
	* Constructeur de Packet
	*/
	PacketDiskFull(int idFile);
	
	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketDiskFull(const Packet& p);
	
	
	/**
	* Destructeur de Data
	*/
	virtual ~PacketDiskFull();
	
	
	int getIdFile ();

private:
	PacketDiskFull() {}

};

#endif // PacketDiskFull_H
