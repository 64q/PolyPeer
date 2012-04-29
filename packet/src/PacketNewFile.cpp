#include <PacketNewFile.hpp>


PacketNewFile::PacketNewFile(int idFile, string fileName, int size) : Packet()
{
	setType (sendOperation);
	
	(*this) << idFile;
	(*this) << fileName;
	(*this) << size;
}

PacketNewFile::PacketNewFile(const Packet& p) : Packet(p)
{

}

PacketNewFile::~PacketNewFile()
{

}

int PacketNewFile::getIdFile ()
{
	setPosition (0);
	int id;
	(*this) >> id;
	return id;
}

string PacketNewFile::getFileName ()
{
	setPosition (1);
	string chaine;
	(*this) >> chaine;
	return chaine;
}

int PacketNewFile::getFileSize ()
{
	setPosition (2);
	int size;
	(*this) >> size;
	return size;
}
