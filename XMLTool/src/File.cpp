#include "../include/File.hpp"

File::File(int id, string path, int size, int chunkSize):
	id(id), filePath(path), size(size), chunkSize(chunkSize)
{
}

File::~File()
{
}

void File::addEntity(Entity* entity)
{
	deploysOn.push_back(entity);
} 
