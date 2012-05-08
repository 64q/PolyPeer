#include <Packet.hpp>


Packet::Packet() : myType(EUndefined), myReadingPosition(0), valid(true)
{

}

Packet::Packet(const Data& d) : myType(EUndefined), myReadingPosition(0), valid(true)
{
	unserialize (d);
}

Packet::Packet(const char* s, unsigned int size) : myType(EUndefined), myReadingPosition(0), valid(true)
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
	data << typeToString(myListData.size());
	data << '/';
	data << typeToString(int(myType));
	data << '/';
	for (unsigned int i = 0; i < myListData.size(); i++)
	{
		data << typeToString(myListData[i].getSize());
		data << '/';
		data << myListData[i];
	}
	return data;
}

int Packet::unserialize (const Data& d)
{
	// init
	myReadingPosition = 0;
	myListData.clear ();
	
	// var
	string extractString; // extraction de valeur
	unsigned int posInData = 0;
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
	
	if ((nbExtraction < 2) && (nbExtraction == nbData))
		return 0;
	else
		return 1;
}

PacketType Packet::getType ()
{
	return myType;
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






