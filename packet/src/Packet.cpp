// Class header
#include <Packet.hpp>

// STL
#include <iostream>
#include <cstring>
#include <string>
#include <math.h>

// Project header

using namespace std;

Packet::Packet() : myType(EUndefined), myReadingPosition(0), valid(true), address("")
{

}

Packet::Packet(const Data& d) : myType(EUndefined), myReadingPosition(0), valid(true), address("")
{
	unserialize (d);
}

Packet::Packet(const char* s, unsigned int size) : myType(EUndefined), myReadingPosition(0), valid(true), address("")
{
	// alloc de 5M max : après ca devient plus soutenable
	if((size > 0) && (size < 5000000))
	{
		Data d (s, size);
		unserialize (d);
	} else
	{
		valid = false;
	}
}

Packet::~Packet()
{
}

Data Packet::serialize ()
{
	Data data;
	// espace pour insérer la taille du paquet -> 32 bits
	// on le fait en caractere pour simplifier (trop de pb avec le décalage de bit)

	for(int j = 0; j < 32;j++)
		data << '0';
//	taille du tableau pour vérif
	data << typeToString(myListData.size());

	//essai new Methode
	/*
	for(int j = 0; j < 4;j++)
		data << '0';
	unsigned int sizeTmp = myListData.size();
	unsigned char dataTmp[4];
	for(int oct=0; oct < 4; oct++)
    {
    	dataTmp[oct] = (sizeTmp%256);
		sizeTmp/=256;

    }
	data.add(data, 4);
	*/


	data << '/';
	// type de paquet
	data << typeToString(int(myType));
	data << '/';
	// insertion des données
	for (unsigned int i = 0; i < myListData.size(); i++)
	{
		data << typeToString(myListData[i].getSize());
		data << '/';
		data << myListData[i];
	}

	// récupération de la taille du paquet
	int size = data.getSize();

	// écriture de la taille sur les 32 premiers octets
	for (unsigned int cpt = 0; cpt < 32; cpt++)
	{
		if(size == 0)
			break;
		if( size%2 == 1)
		{
			data[31-cpt] = '1';
			size--;
		}
		else
			data[31-cpt] = '0';
		size=size/2;
	}

	return data;
}

int Packet::unserialize (const Data& d)
{
	// faire un pré-test -> un paquet sérialisé a une taille mini sûr de 32 octets
	if (d.getSize() <= 32)
	{
		valid = false;
		return 0;
	}

	// vérifier la taille du paquet (les 32 premiers octets)
	unsigned int packetSize = 0;
	for (unsigned int cpt = 0; cpt < 32; cpt++)
	{
		if(d[31-cpt] == '1')
			packetSize += pow(2,cpt);
	}

	if(d.getSize() != packetSize)
	{
		valid = false;
		return 0;
	}


	// EXTRACTION DES DONNEES
	myReadingPosition = 0;
	myListData.clear ();

	// var
	string extractString; // extraction de valeur
	unsigned int posInData = 32;
	int nbExtraction = 0;
	int nbData;
	int size;
	int tmpVal;

	// extraction de la premiere valeur qui correspond au nombre de parametre
	extractString = extract (posInData, d);
	posInData += (extractString.size()+1);
	nbData = stringToType<int>(extractString);

	// extraction du type de paquet
	extractString = extract (posInData, d);
	posInData += (extractString.size()+1);
	tmpVal = stringToType<int>(extractString);
	if ( tmpVal >= int(EUndefined) && tmpVal < int(End_PaquetType))
	{
		myType = PacketType(tmpVal);
	}else
	{
		myType = EUndefined;
	}

	// extraction des autres valeurs
	while (posInData < d.getSize())
	{
		extractString = extract (posInData, d);

		posInData += (extractString.size()+1);
		nbExtraction++;
		size = stringToType<int>(extractString);
		myListData.push_back (Data (d.c_str()+posInData, size));
		posInData += size;
	}

	if (nbExtraction != nbData)
	{
		valid = false;
		return 0;
	}
	else
	{
		valid = true;
		return 1;
	}

}

PacketType Packet::getType ()
{
	return myType;
}

void Packet::setAddress (string addr)
{
	address = addr;
}

string Packet::getAddress () const
{
	return address;
}

void Packet::setType (PacketType p)
{
	myType = p;
}

bool Packet::isValid ()
{
	return valid;
}

unsigned int Packet::getSize ()
{
	return (serialize()).getSize();
}



Data Packet::getDataPos (unsigned int i)
{
	if (i < myListData.size())
	{
		return myListData.at(i);
	}else
	{
		return Data ();
	}
}

void Packet::resetPosition ()
{
	myReadingPosition = 0;
}

void Packet::setPosition (unsigned int i)
{
	if (i < myListData.size())
	{
		myReadingPosition = i;
	} else
	{
		myReadingPosition = myListData.size();
	}
}

bool 	Packet::endOfPacket () const
{
	return !(myReadingPosition < myListData.size());
}

string Packet::extract (unsigned int startPos, const Data& d)
{
	string tmp;
	unsigned int pos = startPos;

	while ((pos < d.getSize()) && (d[pos] != '/'))
	{
		tmp.push_back (d[pos]);
		pos++;
	}
	return tmp;
}

Packet & Packet::operator<< (const Data d)
{
	myListData.push_back (Data (d));
	return *this;
}

Packet & Packet::operator>> (Data& d)
{
	if (!endOfPacket())
	{
		d = myListData[myReadingPosition];
		myReadingPosition++;
	}
	return *this;
}

Packet & Packet::operator<< (const string s)
{
	Data d;
	d<<s;
	myListData.push_back (Data (d));
	return *this;
}

Packet & Packet::operator>> (string& s)
{
	if (!endOfPacket())
	{
		s = myListData[myReadingPosition].getString();
		myReadingPosition++;
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
		i = stringToType<int>(myListData[myReadingPosition].getString());
		myReadingPosition++;
	}
	return *this;
}






