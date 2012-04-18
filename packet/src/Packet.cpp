#include "../include/Packet.hpp"


Packet::Packet() : readingPosition(0)
{

}

Packet::Packet(const Data& d)
{
	
	unserialize (d);
}

Packet::Packet(const char* s, unsigned int size) : readingPosition(0)
{
	Data d (s, size);
	unserialize (d);
}

Packet::~Packet()
{
}

Data Packet::serialize ()
{
	Data data;
	data << typeToString(listData.size());
	data << '/';
	for (unsigned int i = 0; i < listData.size(); i++)
	{
		data << typeToString(listData[i].getSize());
		data << '/';
		data << listData[i];
	}
	return data;
}

int Packet::unserialize (const Data& d)
{
	// init
	readingPosition = 0;
	listData.clear ();
	
	// var
	string value;
	unsigned int pos = 0;
	int numExtraction = 0;
	int nbValue;
	int taille;
	
	// extraction de la premiere valeur qui correspond au nombre
	value = extract (pos, d);
	pos += (value.size()+1);
	nbValue = stringToType<int>(value);
	
	while (pos < d.getSize())
	{
		value = extract (pos, d);
		pos += (value.size()+1);
		numExtraction++;
		taille = stringToType<int>(value);
		
		listData.push_back (Data (d.c_str()+pos, taille));
		pos += taille;
	}
	
	if ((numExtraction < 2) && (numExtraction == nbValue))
		return 0;
	else
		return 1;
}

unsigned int Packet::getSize ()
{
	return (serialize()).getSize();
}

void Packet::resetPosition ()
{
	readingPosition = 0;
}

bool 	Packet::endOfPacket () const
{
	return !(readingPosition < listData.size());
}

string Packet::extract (unsigned int startPos, const Data& d)
{
	string tmp;
	unsigned int pos = startPos;
	
	while ((startPos + pos) < d.getSize() && d[pos] != '/')
	{
		tmp.push_back (d[pos]);
		pos++;
	}
	return tmp;
}

Packet & Packet::operator<< (const Data d)
{
	listData.push_back (Data (d));
	return *this;
}

Packet & Packet::operator>> (Data& d)
{
	if (!endOfPacket())
	{
		d = listData[readingPosition];
		readingPosition++;
	}
	return *this;
}

Packet & Packet::operator<< (const string s)
{
	Data d;
	d<<s;
	
	listData.push_back (Data (d));
	return *this;
}

Packet & Packet::operator>> (string& s)
{
	if (!endOfPacket())
	{
		s = listData[readingPosition].getString();
		readingPosition++;
	}
	return *this;
}

Packet & Packet::operator<< (const int i)
{
	string s = typeToString(i);

	return *this<<s;
}

Packet & Packet::operator>> (int& i)
{
	if (!endOfPacket())
	{
		i = stringToType<int>(listData[readingPosition].getString());
		readingPosition++;
	}
	return *this;
}






