#include <File.hpp>
#include <Zone.hpp>
#include <OpenFileException.hpp>

using namespace std;

File::File(int id, string name, string path, int size, int chunkSize, FileState fs):
	name(name), 
	fState(fs)
{
	try 
	{
		fileM = new FileManager(path.data(), (long)size, (long)chunkSize, id);

	} catch (OpenFileException)
	{
		fState = ERROR;
		cout << "FAIL LOAD : Fichier " << path << " inexistant"<< endl;
	}
}

File::File(int id, string name, string path, int size, int chunkSize):
	name(name),
	fState(READY)
{
	try 
	{
		fileM = new FileManager(path.data(), (long)size, (long)chunkSize, id);

	} catch (OpenFileException)
	{
		fState = ERROR;
		cout << "FAIL LOAD : Fichier " << path << " inexistant"<< endl;
	}

}

File::File(int id, string name, string path):
	name(name),
	fState(READY)
{
	try 
	{
			fileM= new FileManager(path.data(), id);

	} catch (OpenFileException)
	{
		fState = ERROR;
		cout << "FAIL LOAD : Fichier " << path << " inexistant"<< endl;
	}
}

File::~File()
{
	delete (fileM);
}

void File::setFileState(FileState fs)
{
	fState = fs;
}

vector<vector<Entity*>* >* File::getSortedHosts()
{
	unsigned int i,j;

	vector<vector<Entity*>* >* toReturn = new vector<vector<Entity*>* >();
	
	bool find = false;
	
	for(i=0;i<deploysOn.size();i++) 
	{
		Entity* host = deploysOn[i];

		find = false;
		for (j=0;j<toReturn->size();j++)
		{
			Entity* host2 = (*(*toReturn)[j])[0];
			if (host->getParent() == host2->getParent())
			{
				((*toReturn)[j])->push_back(host);
				find = true;
			}
			
		}
		if (find == false)
		{
			toReturn->push_back(new vector<Entity*> (1,host));
		}
	
	}
	
	return toReturn;
}

void File::deleteSortedHost(vector<vector<Entity*>* >* entities)
{
	for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
		delete (*itZone);
	delete entities;
}

void File::addEntity(Entity* entity)
{
	map<string, Entity*>* entities;
	
	if (entity != NULL)
	{
		entities = entity->getEntities();
		if ( entities != NULL)
		{
			map<std::string,Entity*>::const_iterator
			mit (entities->begin()),
			mend(entities->end());
			for(; mit!=mend; ++mit) 
			{	
				if (mit->second->getIP() != NULL)
				{
					deploysOn.push_back(mit->second);
					mit->second->addDeploymentState(0, this, HDS_WAIT);
				}
				if (mit->second->getEntities() != NULL)
					addEntity(mit->second);
			}
		} else 
		{
			deploysOn.push_back(entity);
			entity->addDeploymentState(0, this, HDS_WAIT);
		}
	}
}

