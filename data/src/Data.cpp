#include <Data.hpp>


Data::Data () 
{ 
	data = 0;
	size = 0;
	realSize = 8;
	data = new char [realSize]; 
}

Data::~Data () 
{
	if (data != 0) delete [] data;
}

Data::Data (const Data& other) : data(0), size(other.size), realSize(other.realSize)
{
	data = new char [realSize];
	
	memcpy (data, other.data, size);	
}

Data::Data ( const char* s, unsigned int size ) : data(0), size(0), realSize(8)
{
	data = new char [realSize];
	add (s, size);
}

Data& Data::operator=(const Data& other)
{
	size = other.size;
	realSize = other.realSize;
	
	if (data != 0)
		delete [] data;
	data = new char [realSize];

	memcpy (data, other.data, size);

	return *this;
}

const char& Data::operator[] ( unsigned int pos ) const
{
	return data[pos];
}

char& Data::operator[] ( unsigned int pos )
{
	return data[pos];
}


void Data::resize ( unsigned int size )
{
	unsigned int tmpS = realSize;
	realSize = 8;
	while (realSize < size)
		realSize *= 2; // doubler la capacité de stockage

	//cout << "taille demandé : " << size<< " taille actuelle : " << this->size << " nvll actu : " << realSize << " min : " << min (this->size, size) << endl;
	if (realSize != tmpS)
	{
		char* tmp = new char [realSize];
		memcpy (tmp, data, min (this->size, size));
		if (data != 0)
			delete [] data;
		data = tmp;
	}

	this->size = size;
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

bool Data::empty () const
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
	int length = s.length();
	resize (this->size + length);
	for (int i = 0; i < length; i++)
		data[this->size-length+i] = s.at(i);

	return *this;
}

Data& Data::add ( const Data& d )
{
	int length = d.getSize();
	resize (this->size + length);
	for (int i = 0; i < length; i++)
		data[this->size-length+i] = d[i];
	
	return *this;
}


void Data::c_str ( char* s ) const
{
	memcpy (s, data, size);
}

const char* Data::c_str () const
{
	return data;
}

string Data::getString () const
{
	return (string (c_str(), getSize()));
}

void Data::print ()
{
	std::cout << data << std::endl;
}


