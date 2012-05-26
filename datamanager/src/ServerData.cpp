#include <ServerData.hpp>

using namespace std;

ServerData::ServerData()
{
	cM = new ConnectionManager(6666);
	addressServ = "192.168.0.1";
	xmlTool = new XMLTool(this);
}

ServerData::~ServerData()
{
	delete cM;
	vector <string> alreadyDelete;
	deleteDeployFiles();
	deleteHosts();
	//deleteMap(this->getEntities(), alreadyDelete);

}

/*void ServerData::deleteMap(map<string, Entity*>* entities, vector<string> &alreadyDelete)
{
	map<std::string,Entity*>::iterator
	mit (entities->begin()),
	mend(entities->end());
	map<std::string,Entity*>::iterator tmpIt;
	
	while (mit != mend)
	{
		if (mit->second != NULL)	
		{	
			if (alreadyDelete.(mit->first) == -1)
			{
				if (mit->second->getEntities() != NULL)
				{
					deleteMap(mit->second->getEntities(), alreadyDelete);
					delete(mit->second);
					alreadyDelete.push_back(mit->first);
					entities->erase(mit);
				}
				mit++;
			}
		}		
	}
}*/

void ServerData::deleteDeployFiles()
{
	unsigned int i;
	for (i=0;i<deployFiles.size();i++)
	{
		delete deployFiles[i];
	}
}

void ServerData::deleteHosts()
{
	unsigned int i;
	for (i=0;i<hosts.size();i++)
	{
		delete hosts[i];
	}
}

XMLTool* ServerData::getXMLTool()
{
	return xmlTool;
}

map<string, Entity*>* ServerData::getEntities()
{
	return &entities;
}

vector<File*>* ServerData::getDeployFiles()
{
	return &deployFiles;
}

ConnectionManager* ServerData::getConnectionManager()
{
	return cM;
}

string ServerData::getAddressServ()
{
	return addressServ;
}

void ServerData::updateHost(string addressHost, int fileID, int nbChunk)
{
	unsigned int i=0;
	bool find = false;
	Entity* host = getHostByAddress(addressHost);
	vector<DeploymentState>* dState = host->getDeploys();
	
	while( (i < dState->size()) && (find == false) )
	{
		if (((*dState)[i]).getId() == fileID )
		{
			find = true;
			((*dState)[i]).setCurrentIdChunk(nbChunk);
		}
		i++;
	}	
}

void ServerData::updateHost(string addressHost, int fileID, State s)
{
	unsigned int i=0;
	bool find = false;
	Entity* host = getHostByAddress(addressHost);
	vector<DeploymentState>* dState = host->getDeploys();
	
	host->setHostState(s);
	
	while( (i < dState->size()) && (find == false) )
	{
		if (((*dState)[i]).getId() == fileID )
		{
			find = true;
			((*dState)[i]).setCurrentState(s);
		}
		i++;
	}
}


void ServerData::updateHost(string addressHost, State s)
{
	Entity* host = getHostByAddress(addressHost);
	host->setHostState(s);
}


FileManager* ServerData::addFile(File* f)
{
	deployFiles.push_back(f);
	return f->getFileManager();
}

void ServerData::addFileToAll(File* f)
{
	unsigned int i;
	addFile(f);
	xmlTool->writeFileIntoDeployments(f);
	for(i=0; i < (f->getDeploysOn())->size(); i++)
	{
		xmlTool->writeEntityIntoFile((f->getFileManager())->getIdFile(), (*(f->getDeploysOn()))[i]);
	}
}

int ServerData::getCurrentId()
{
	int currentId=0;
	unsigned int i;
	for (i=0;i<deployFiles.size();i++)
	{
		if (currentId < (deployFiles[i]->getFileManager())->getIdFile())
			currentId = (deployFiles[i]->getFileManager())->getIdFile();
	}
	
	return currentId;
}

File* ServerData::getFile(int id)
{
	unsigned int i=0;
	bool find = false;
	File* toReturn = NULL;

	while( (i < deployFiles.size()) && (find == false) )
	{
		if ((deployFiles[i]->getFileManager())->getIdFile() == id )
		{
			find = true;
			toReturn = deployFiles[i];
		}
		i++;
	}
	return toReturn;	
}

Entity* ServerData::addHost(string name, Entity* parent, int networkCapacity, string address)
{
	Entity* host = new Host(name, parent, networkCapacity, address);
	hosts.push_back(host);
	return host;
}

vector<Entity*>* ServerData::getHosts()
{
	return &hosts;
}

Entity* ServerData::getHostByAddress(string address)
{
	unsigned int i=0;
	bool find = false;
	Entity* toReturn = NULL;

	while( (i < hosts.size()) && (find == false) )
	{
		if (!((*(hosts[i]->getIP())).compare(address)))
		{
			find = true;
			toReturn = hosts[i];
		}
		i++;
	}
	return toReturn;		
}

Entity* ServerData::getHostByName(string name)
{
	unsigned int i=0;
	bool find = false;
	Entity* toReturn = NULL;

	while( (i < hosts.size()) && (find == false) )
	{
		if (!((hosts[i]->getName()).compare(name)))
		{
			find = true;
			toReturn = hosts[i];
		}
		i++;
	}
	return toReturn;		
}

FileManager* ServerData::getFileManager(int id)
{
	unsigned int i=0;
	bool find = false;
	FileManager* toReturn = NULL;

	while( (i < deployFiles.size()) && (find == false) )
	{
		if ((deployFiles[i]->getFileManager())->getIdFile() == id )
		{
			find = true;
			toReturn = deployFiles[i]->getFileManager();
		}
		i++;
	}
	return toReturn;		
}
	
void ServerData::displayEntities(map<string, Entity*>* entities, int level)
{
	unsigned int i;
	map<std::string,Entity*>::const_iterator
	mit (entities->begin()),
	mend(entities->end());
		
	for(; mit!=mend; ++mit) 
	{
		if (mit->second->getParent() != NULL)
			cout << string( level*3, ' ' ) << mit->first << " | " << "capacity : "<< mit->second->getNetworkCapacity()<< " " << " | " << "parent : "<< (mit->second->getParent())->getName();		
		if (mit->second->getEntities() != NULL)
		{
			cout << endl;
			displayEntities(mit->second->getEntities(), level + 1);
		}
		if (mit->second->getDeploys() != NULL)
		{
			if (!((mit->second->getDeploys())->empty()))
			{
				for (i=0; i < (mit->second->getDeploys())->size(); i++)
				{
					cout << " | fID : " << (((*(mit->second->getDeploys()))[i]).getRefFile())->getFileManager()->getIdFile();
					cout << " | cID : " << (*(mit->second->getDeploys()))[i].getCurrentIdChunk();
					cout << " | fPath : " << ((*(mit->second->getDeploys()))[i].getRefFile())->getFileManager()->getFileName();
					cout << " | hState : " << (*(mit->second->getDeploys()))[i].getCurrentState();
					cout << endl;
					cout << string( level*3 + (mit->first).size(), ' ' ) << " " ;
				}
			}
		}
		cout << endl;
		
	}
}

Entity* ServerData::getEntity(map<string, Entity*>* entities, string entityName)
{
	Entity* toReturn = NULL;
	map<std::string,Entity*>::const_iterator
	mit (entities->begin()),
	mend(entities->end());
	
	for(; mit!=mend; ++mit) 
	{	
		if (toReturn == NULL)
		{
			if (!((mit->second->getName()).compare(entityName)))
				toReturn = mit->second;
			else if (mit->second->getEntities() != NULL)	
				toReturn = getEntity(mit->second->getEntities(), entityName);
		}
	}

	return toReturn;
}

void ServerData::fillAddressList(Entity* entity, list<string> &list)
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
					list.push_back(*(mit->second->getIP()));
				if (mit->second->getEntities() != NULL)
					fillAddressList(mit->second, list);
			}
		} else 
			list.push_back(*(entity->getIP()));
	}
}

void ServerData::public_displayEntities() 
{ 
	displayEntities(getEntities()); 
}

Entity* ServerData::public_getEntity(string entityName) 
{ 
	return getEntity(&entities, entityName); 
}

void ServerData::public_fillAddressList(string entityName, list<string> &list) 
{
	Entity* entity;
	entity = getEntity(&entities, entityName);
	fillAddressList(entity, list); 
}

