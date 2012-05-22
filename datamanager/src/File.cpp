#include <File.hpp>

File::File(int id, string path, int size, int chunkSize)
{
	fileM = new FileManager(path.data(), (long)size, (long)chunkSize, id);
}

File::~File()
{
	delete fileM;
}

void File::addEntity(Entity* entity)
{
	deploysOn.push_back(entity);
} 
