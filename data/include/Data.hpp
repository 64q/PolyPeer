#ifndef DATA_H
#define DATA_H



/*
 * Classe Data
 *
 * Permet de stocker un contenu quelconque car il n'y a pas de 
 * 	traitement ou d'interprétation des valeurs ajoutés
 * Sérialiser sous forme de chaine de caractères (char*)
 *
 * par Olivier
 */


// standard
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

class Data
{
private:
	// conteneur
	char* data;
	// taille
	unsigned int size;
	
	// optimisation : taille réellement alloué. Double à chaque nouvelle allocation
	unsigned int realSize;


public:
	/**
	 * Constructeur de Data
	 */
	Data ();
	
	/**
	 * Destructeur de Data
	 */
	~Data ();
	
	/**
	 * Constructeur par copie de Data
	 * @param const Data&
	 * 	le Data à copier
	 */
	Data ( const Data& other );
	
	/**
	 * Constructeur a partir d'une chaine de données
	 * @param const char*
	 * 	le Data à copier
	 * @param unsigned int
	 *	sa taille
	 */
	Data ( const char* s, unsigned int size );
	
	/**
	 * Opérateur de copie
	 */
	Data& operator= ( const Data& other );
	
	/**
	 * Opérateur d'accès lecture seule
	 * @return const char&
	 * 	retourne une valeur de data
	 */
	const char& operator[] ( unsigned int pos ) const;
	
	/**
	 * Opérateur d'accès avec modification
	 * @return const char&
	 * 	retourne une valeur de data
	 */
	char& operator[] ( unsigned int pos );
	
	/**
	 * Taille du conteneur
	 * @return unsigned int
	 * 	retourne la taille du conteneur
	 */
	unsigned int getSize () const { return size; }
	
	/**
	 * Redéfinir la taille de la chaine
	 * 	si la taille demandée est plus petites
	 * 	les données en trop sont supprimées
	 */
	void resize ( unsigned int size );
	
	/**
	 * Vide le conteneur et le réinitialise
	 */
	void clear ();
	
	/**
	 * Taille du conteneur
	 * @return bool
	 * 	retourne vrai si le conteneur est vide
	 */
	bool empty () const;
	
	/**
	 * Ajouter une chaine de caractères au conteneur
	 * @param const char*
	 *	chaine à ajouter
	 * @param int
	 *	taille de la chaine
	 * @return Data&
	 * 	référence sur le data modifié
	 */
	Data& add ( const char* s, unsigned int size );
	
	/**
	 * Ajouter un caractère (ou une données de 8 bits)
	 * @param char
	 *	donnée à ajouter
	 * @return Data&
	 * 	référence sur le data modifié
	 */
	Data& add ( char c );
	
	/**
	 * Ajouter d'une chaine de caractère string
	 * @param const string&
	 *	chaine à ajouter
	 * @return Data&
	 * 	référence sur le data modifié
	 */
	Data& add ( const string& s );
	
	/**
	 * Ajouter un conteneur
	 * @param const Data&
	 *	conteneur à ajouter
	 * @return Data&
	 * 	référence sur le data modifié
	 */
	Data& add ( const Data& s );
	
	/**
	 * Récupérer le contenu de Data sous forme d'un tableau de char
	 * @param char*
	 *	chaine qui doit contenir Data (préalablement initialisé à la taille du conteneur) 
	 */
	void c_str ( char* s) const;
	
	/**
	 * Récupérer le contenu de Data sous forme d'un tableau de char
	 * @return char*
	 *	chaine qui doit contenir Data (préalablement initialisé à la taille du conteneur) 
	 * /!\ Ne pas corrompre les données de cette chaine
	 */
	const char* c_str () const;
	
	/**
	 * Récupérer le contenu de Data avec un string
	 * @return string
	 */
	string getString () const;
	
	/**
	 * Affichage du contenu pour les test
	 */
	void print ();
	
	
	
	// Les fonctions suivantes permettent une utilisation rapide des fonctions add ( ... );
	
	Data& operator+= ( char c ) { return add ( c ); }
	Data& operator+= ( const string& s ) { return add ( s ); }
	Data& operator+= ( const Data& d ) { return add ( d ); }
	
	Data& operator<< ( char c ) { return add ( c ); }
	Data& operator<< ( const string& s ) { return add ( s ); }
	Data& operator<< ( const Data& d ) { return add ( d ); }

	
};

#endif
