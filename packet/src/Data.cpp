#include "../include/Data.hpp"

Data::Data (const Data& other) : data(0), size(other.size), realSize(other.realSize)
{
	data = new char [realSize];

	for (unsigned int i = 0; i < size; i++)
		data[i] = other.data[i];	
}

Data& Data::operator=(const Data& other)
{
	size = other.size;
	realSize = other.realSize;
	
	if (data != 0)
		delete [] data;
	data = new char [realSize];

	for (unsigned int i = 0; i < size; i++)
		data[i] = other.data[i];	

	return *this;
}

char Data::operator[] ( unsigned int i ) const
{
	if (i >= 0 && i < size)
		return data[i];
	else
		return ' ';
}


int Data::resize ( unsigned int size )
{
	if ( this->realSize < size)
	{
		realSize *= 2; // doubler la capacité de stockage
		
		char* tmp = new char [realSize];
		for (unsigned int i = 0; i < size-1; i++)
			tmp[i] = data[i];
		// utiliser memcpy () ! memcpy (tmp, data, size);
		delete [] data;
		data = tmp;
	}
	this->size = size;
	return 1;
}

void Data::clear ()
{
	if (realSize != 8)
	{
		delete [] data;
		data = new char [8];
	}
	realSize = 8;
	size = 0;
}

int Data::empty () const
{
	return (size == 0);
}

Data& Data::add ( const char* s, unsigned int size )
{
	resize (this->size + size);
	for (unsigned int i = 0; i < size; i++)
		data[this->size-size+i] = s[i];
	return *this;
}

Data& Data::add ( char c )
{
	resize (size+1);
	data[size-1] = c;
	return *this;
}

Data& Data::add ( const string& s )
{
	int length = s.size();
	resize (this->size + length);
	for (unsigned int i = 0; i < size; i++)
		data[this->size-length+i] = s[i];
	return *this;
}

Data& Data::add ( const Data& d )
{
	int length = d.length();
	resize (this->size + length);
	for (unsigned int i = 0; i < size; i++)
		data[this->size-length+i] = d[i];
	return *this;
}

/*
Data& Data::insert ( const char* s, unsigned int size, unsigned int pos )
{
	return *this;
}

Data& Data::insert ( char c, unsigned int pos )
{
	return *this;
}*/

void Data::serialize ( char* s )
{
	if (s != 0)
	{
		for (unsigned int i = 0; i < size; i++)
			s[i] = data[i];
	}
}



