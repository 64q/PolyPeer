#include <string>
#include "../include/Chunk.hpp"
#include "../include/md5.hpp"

MD5 Chunk::encoder;

Chunk::Chunk(long number, long size, char* data)
{
	initialiser(number, size, data);
	chunkIntegrity = true;
}

Chunk::Chunk(long number, long size, char* data, char* crc)
{
	initialiser(number, size, data);

	//vérification de l'égalité entre le crc calculé dans initaliser et celui passé en paramètre
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
	}
	else
	{
		chunkIntegrity = true;
	}
}

void Chunk::initialiser(long number, long size, char* data)
{
	this->number = number;

	this->size = size;

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
