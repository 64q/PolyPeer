#ifndef PacketSendOperationFinished_H
#define PacketSendOperationFinished_H


/*
 * Classe PacketSendOperationFinished
 *
 * Hérite de la classe Packet
 * Gérer un type de packet spécifique
 *
 *
 * par Olivier
 */


// Project header
#include <Packet.hpp>

using namespace std;

class PacketSendOperationFinished : public Packet
{
private:

public:
	/**
	* Constructeur de Packet
	*/
	PacketSendOperationFinished();
	
	/**
	* Constructeur sur un Packet (une maniere de caster un Packet)
	*/
	PacketSendOperationFinished(const Packet& p);
	
	/**
	* Destructeur de Data
	*/
	virtual ~PacketSendOperationFinished();
	
};

#endif // PacketSendOperationFinished_H
