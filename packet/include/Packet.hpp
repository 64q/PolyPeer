#ifndef PACKET_H
#define PACKET_H


/*
 * Classe Packet
 *
 * Permet de stocker de manière organisé et rapide les données
 * Le but étant de stocker ces données afin de pouvoir les sérialiser
 * 	ou les désérialiser facilement
 *
 * par Olivier
 */


// Entêtes
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

#ifdef _MSC_VER
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include "Data.hpp"	// pour gérer le conteneur

using namespace std;


class Packet
{
private:
    // données du packet
    vector<Data> listData;
    
    // position d'extraction
	unsigned int readingPosition;
	

public:
	/**
	* Constructeur de Packet
	*/
	Packet();
	
	/**
	* Constructeur de Packet
	*/
	Packet(const Data& d);
	
	/**
	* Constructeur de Packet
	*/
	Packet(const char* s, unsigned int size);
	
	/**
	* Destructeur de Data
	*/
	virtual ~Packet();
	
	/**
	 * Récupérer le contenu du Packet sous forme de Data
	 * @return Data
	 *	contenu sérialisé du paquet 
	 */
	Data serialize ();
	
	/**
	 * Recréer le paquet avec un contenu sérialisé
	 * @return int
	 *	retourne 0 si il y a une erreur sur l'extraction du paquet 
	 */
	int unserialize (const Data& d);
	
	/**
	 * Retourne s'il reste des infos à extraire du paquet
	 * @return bool
	 *	retourne 0 s'il n'y a plus d'argument
	 */
	bool endOfPacket () const;
	
	/**
	 * Retourne la taille du paquet
	 * @return unsigned int
	 *	taille
	 * Méthode à ne pas trop utiliser... calculs lourds
	 */
	unsigned int getSize ();
	
	/**
	 * Remet à zéro la position de lecture des arguments
	 *  le premier argument est la première information entrée dans le paquet.
	 */
	void resetPosition ();
	
	/**
	 * Insérer une donnée dans le paquet
	 * @param const Data d
	 *  Une Data à insérer
	 * @return Packet&
	 *	ref sur le paquet traité
	 */
	Packet & operator<< (const Data d);
	
	/**
	 * Recupérer une donnée dans le paquet
	 * @param Data& d
	 *  la Data a remplir
	 * @return Packet&
	 *	ref sur le paquet traité
	 */
	Packet & operator>> (Data& d);
	
	// idem pour le reste
	
	Packet & operator<< (const string s);
	Packet & operator>> (string& s);
	
	Packet & operator<< (const int);
	Packet & operator>> (int& i);
	
	/*
	Packet & 	operator>> (float &Data)
	Packet & 	operator>> (double &Data)
	*/

private:
	
	string extract (unsigned int startPos, const Data& d);
	
	template<class Type> std::string typeToString(Type source)
	{
		// créer un flux de sortie
		std::ostringstream ossValue;
		ossValue << source;
		// récupérer une chaîne de caractères
		return ossValue.str();
	}
	
	template<class Type> Type stringToType(std::string source)
	{
		// creer le flux
		istringstream iss(source);
		// affecter les nouvelles valeurs
		Type tmp;
		iss>>tmp;
		return tmp;
	}


};

#endif // PACKET_H
