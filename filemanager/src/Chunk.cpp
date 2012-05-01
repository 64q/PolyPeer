#include <string>
#include <sstream>
#include <iostream>
#include <Chunk.hpp>
#include <md5.hpp>

using namespace std;
MD5 Chunk::encoder;

Chunk::Chunk(long number, long size, char* data, int idFile)
{
	initialiser(number, size, data, idFile);
	chunkIntegrity = true;
}

Chunk::Chunk(long number, long size, char* data, int idfile, char* crc)
{
	initialiser(number, size, data, idFile);
	checkIntegrity(crc);

}

void Chunk::checkIntegrity(char* crc)
{
	//vérification de l'égalité entre le crc calculé dans initaliser() et celui passé en paramètre
	bool equal = true;
	for (int i = 0; i < 32; i++)
	{
		if (md5[i]!=crc[i])
		{
			equal = false;
		}
	}
	if(!equal)
	{
		chunkIntegrity = false;
		if(number<20)
		{
			cout<<number<<endl;
		cout.write(md5, 32)<<endl;
		cout.write(crc, 32)<<endl;

		}

	}
	else
	{
		chunkIntegrity = true;

	}
}

void Chunk::initialiser(long number, long size, char* data, int idFile)
{
	this->number = number;

	this->size = size;
	this->idFile = idFile;
	//copie de data
	this->data = new char[size];
	for (int i = 0; i < size; i++)
	{
		this->data[i] = data[i];
	}

	//calcul du code correspondant à data
	this->md5 = encoder.digestString(data, size);
}

Chunk::~Chunk()
{
	delete[] data;

}

long Chunk::getNumber()
{
	return number;
}

char* Chunk::getData()
{
    return data;
}
long Chunk::getSize()
{
	return size;
}

char* Chunk::getMD5()
{
	return md5;
}

bool Chunk::isIntegrate()
{
	return chunkIntegrity;
}

int Chunk::getIdFile()
{
	return idFile;
}

char* Chunk::serialize(int& length)
{
	stringstream out(stringstream::in|stringstream::out | stringstream::binary);
    out << idFile << "|" << number << "|" << md5 << "|" << size << "|";
    out.write(data, size);


    out.seekg (0, ios::end);
	length = out.tellg();
	out.seekg (0, ios::beg);

	char* serializedChunk = new char[length];
	out.read(serializedChunk, length);
	return serializedChunk;
}

Data Chunk::serialize()
{
	int size;
	char* chaine;
	chaine = serialize(size);
	return Data (chaine, size);
}

Chunk::Chunk(char* serializedChunk, int sizeString)
{

	stringstream in(stringstream::in | stringstream::out| stringstream::binary);
	in.write(serializedChunk, sizeString);

	in>>idFile;
	//cout<<idFile<<endl;
	int p = in.tellg();
	in.seekg(p+1, ios::beg);
	in>>number;
	//cout<<number<<endl;

	p = in.tellg();
	in.seekg(p+1, ios::beg);
	char* crc = new char[32];
	in.read(crc, 32);
	//cout.write(crc, 32)<<endl;




	p = in.tellg();
	in.seekg(p+1, ios::beg);
	in>>size;
	//cout<<size<<endl;


	p = in.tellg();
	in.seekg(p+1, ios::beg);
	data = new char[size];
	in.read(data, size);
	//cout.write(data, size)<<endl;


	//calcul du code correspondant à data
	this->md5 = encoder.digestString(data, size);
	checkIntegrity(crc);
}

Chunk::Chunk(Data& d)
{
	//convertion

	int sizeString = int(d.getSize());
	char* serializedChunk = new char[sizeString];

	d.c_str (serializedChunk);

	stringstream in(stringstream::in | stringstream::out| stringstream::binary);
	in.write(serializedChunk, sizeString);

	in>>idFile;
	//cout<<idFile<<endl;
	int p = in.tellg();
	in.seekg(p+1, ios::beg);
	in>>number;
	//cout<<number<<endl;

	p = in.tellg();
	in.seekg(p+1, ios::beg);
	char* crc = new char[32];
	in.read(crc, 32);
	//cout.write(crc, 32)<<endl;




	p = in.tellg();
	in.seekg(p+1, ios::beg);
	in>>size;
	//cout<<size<<endl;


	p = in.tellg();
	in.seekg(p+1, ios::beg);
	data = new char[size];
	in.read(data, size);
	//cout.write(data, size)<<endl;


	//calcul du code correspondant à data
	this->md5 = encoder.digestString(data, size);
	checkIntegrity(crc);

	// vidage
	delete [] serializedChunk;
}




