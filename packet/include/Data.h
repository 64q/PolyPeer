#ifndef DATA_H
#define DATA_H


#include <iostream>
#include <string>


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
	Data () : data(0), size(0), realSize(8) { data = new char [realSize]; }
	~Data () {if (data != 0) delete [] data;}
	
	Data (const Data& other);

	Data& operator= ( const Data& other );
	char operator[] ( unsigned int i ) const;
	
	Data& operator+= ( char c ) { return add ( c ); }
	Data& operator+= ( const string& s ) { return add ( s ); }
	Data& operator+= ( const Data& d ) { return add ( d ); }
	Data& operator<< ( char c ) { return add ( c ); }
	Data& operator<< ( const string& s ) { return add ( s ); }
	Data& operator<< ( const Data& d ) { return add ( d ); }


	unsigned int length () const { return size; }
	int resize ( unsigned int size );
	void clear ();
	int empty () const;
	
	Data& add ( const char* s, unsigned int size );
	Data& add ( char c );
	Data& add ( const string& s );
	Data& add ( const Data& s );

	void serialize ( char* s);
};

#endif
