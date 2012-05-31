#include <File.hpp>
#include <Zone.hpp>
#include <OpenFileException.hpp>
#include <CreateFileException.hpp>

using namespace std;

File::File(int id, string name, string serverPath, string clientPath, int chunkSize, FileState fs, long dateFile):
	name(name),
	clientPath(clientPath),
	fState(fs)
{
	// interdire d'autre state que FINISH et READY
	if((fState != FINISH) && (fState != F_PAUSE))
		fState = READY;

	try
	{
		fileM = new FileManager(serverPath.data(), id);
		date = (time_t) dateFile;

	} catch (OpenFileException)
	{
		fileM = NULL;
		fState = F_ERROR;
		cout << "FAIL LOAD : Fichier " << serverPath << " inexistant ou déjà ouvert par un autre déploiement "<< endl;
		throw CreateFileException();
	}
}

File::File(int id, string name, string serverPath, string clientPath, int chunkSize):
	name(name),
	clientPath(clientPath),
	fState(READY)
{
	try
	{
		fileM= new FileManager(serverPath.data(), id);
		time ( &date );

	} catch (OpenFileException)
	{
		fileM = NULL;
		fState = F_ERROR;
		cout << "FAIL LOAD : Fichier " << serverPath << " inexistant"<< endl;
		throw CreateFileException();
	}

}

File::File(int id, string name, string serverPath, string clientPath):
	name(name),
	clientPath(clientPath),
	fState(READY)
{
	try
	{
		fileM= new FileManager(serverPath.data(), id);
		time ( &date );

	} catch (OpenFileException)
	{
		fileM = NULL;
		fState = F_ERROR;
		cout << "FAIL LOAD : Fichier2 " << serverPath << " inexistant"<< endl;
		throw CreateFileException();
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
	if(entities != NULL)
	{
		for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
			delete (*itZone);
		delete entities;
	}
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
				if (mit->second->getType() == HOST)
				{
					deploysOn.push_back(mit->second);
					mit->second->addDeploymentState(0, this, HDS_INIT);
				}
				if (mit->second->getEntities() != NULL)
					addEntity(mit->second);
			}
		} else
		{
			if (getEntity(entity->getName()) == NULL)
			{
				deploysOn.push_back(entity);
				entity->addDeploymentState(0, this, HDS_INIT);
			}
		}
	}
}

Entity* File::getEntity(string name)
{
	unsigned int i=0;
	bool find = false;
	Entity* toReturn = NULL;

	while( (i < deploysOn.size()) && (find == false) )
	{
		if (!((deploysOn[i]->getName()).compare(name)))
		{
			find = true;
			toReturn = deploysOn[i];
		}
		i++;
		
	}
	return toReturn;	
}

