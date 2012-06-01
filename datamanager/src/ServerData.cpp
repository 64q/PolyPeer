#include <ServerData.hpp>
#include <PolypeerServer.hpp>

using namespace std;

ServerData::ServerData() :
	addressServ("192.168.0.50"),
	clientPort(5555)
{
	cM = new ConnectionManager(6666);
	cM->start();
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

Mutex* ServerData::getMutex()
{
	return &mutex_deployFiles;
}

void ServerData::updateHost(string addressHost, int fileID, int nbChunk)
{
	Entity* host = getHostByAddress(addressHost);
	if(host != NULL)
	{
		// Actualiser le nombre de chunck pour l'host
		if (host->getDeploymentState(fileID) != NULL)
		{
			host->getDeploymentState(fileID)->setCurrentIdChunk(nbChunk);
			// l'host a fini son operation
			host->setHostState(WAIT);
			// Actualiser l'état du fichier POUR L'Host
			if(nbChunk >= getFile(fileID)->getFileManager()->getNumberChunk())
				host->getDeploymentState(fileID)->setCurrentState(HDS_FINISH);
			else
				host->getDeploymentState(fileID)->setCurrentState(HDS_WAIT);
		} else 
		{
			cout << "Le fichier d'id donné n'existe pas ("<<fileID<<")" << endl;
		}
		// l'host a fini son operation
		host->setHostState(WAIT);
	}
	
}

void ServerData::updateHost(string addressHost, int fileID, HostDeployState s)
{
	Entity* host = getHostByAddress(addressHost);
	if(host != NULL)
	{
		// l'host a fini son operation
		host->setHostState(WAIT);
		// Actualiser l'état du fichier POUR L'Host
		if(host->getDeploymentState(fileID) != NULL)
			host->getDeploymentState(fileID)->setCurrentState(HDS_DISKFULL);
	}
}


void ServerData::updateHost(string addressHost, HostState s)
{
	Entity* host = getHostByAddress(addressHost);
	if(host != NULL)
		host->setHostState(s);
}


void ServerData::updateHostInit(string addressHost)
{
	Entity* host = getHostByAddress(addressHost);
	if(host != NULL)
	{
		host->setHostState(OFFLINE);
		for (vector<DeploymentState>::iterator itDeploy = host->getDeploys()->begin(); itDeploy != host->getDeploys()->end(); itDeploy++)
		{
			(*itDeploy).setCurrentState(HDS_INIT);
		}
	}
}

FileManager* ServerData::addFile(File* f)
{
	mutex_deployFiles.lock();
	deployFiles.push_back(f);
	mutex_deployFiles.unlock();
	
	return f->getFileManager();
}

void ServerData::addFileToAll(File* f)
{
	unsigned int i;
	addFile(f);
	if (f->getFileState() != F_ERROR)
	{
		xmlTool->writeFileIntoDeployments(f);
		for(i=0; i < (f->getDeploysOn())->size(); i++)
		{
			xmlTool->writeEntityIntoFile((f->getFileManager())->getIdFile(), (*(f->getDeploysOn()))[i]);
		}
	}
}

int ServerData::getCurrentId()
{
	return xmlTool->getCurrentId();
}

File* ServerData::getFile(int id)
{
	unsigned int i=0;
	bool find = false;
	File* toReturn = NULL;
	
	
	while( (i < deployFiles.size()) && (find == false) )
	{
		if (deployFiles[i]->getFileManager())
		{
			if ((deployFiles[i]->getFileManager())->getIdFile() == id )
			{
				find = true;
				toReturn = deployFiles[i];
			}
		}
		i++;
	}

	return toReturn;	
}

void ServerData::deleteFile(int id)
{
	File* f = getFile(id);
	vector<File*>::iterator
	vit (deployFiles.begin()),
	vend(deployFiles.end());
	
	if (f != NULL)
	{
		if (f->getFileState() != FINISH)
			xmlTool->removeDeployment(id);
	}
		
	for(; vit!=vend; ++vit) 
	{
		if ((*vit)->getFileManager() != NULL)
		{
			if (((*vit)->getFileManager())->getIdFile() == id )
			{
				deployFiles.erase(vit);
				break;
			}
		}
	}
	
}

Entity* ServerData::addHost(string name, Entity* parent, int networkCapacity, string address, string mac)
{
	Entity* host = new Host(name, parent, networkCapacity, address, mac);
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
		if (!((hosts[i]->getIP()).compare(address)))
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
		if (deployFiles[i]->getFileManager() != NULL)
		{
			if ((deployFiles[i]->getFileManager())->getIdFile() == id )
			{
				find = true;
				toReturn = deployFiles[i]->getFileManager();
			}
		}
		i++;
	}
	return toReturn;		
}

bool ServerData::updateNetworkCurrentBroadbandSpeed(Entity* entity, int packetWeight)
{
	bool possible = true;
	
	// racine de l'arbre
	if(entity != NULL)
	{
		// init de la valeur témoin
		entity->setCurrentBroadbandSpeed(0);
		// si on peut envoyer
		if(entity->getTimerState())
		{
			possible = updateNetworkCurrentBroadbandSpeed(entity->getParent(),packetWeight);
			if(possible)
			{
				// calcul
				int capacite = entity->getNetworkCapacity();
				int neededTimeMs = (packetWeight*1000)/capacite;
				
				entity->setTimerSpeed(neededTimeMs/1000, neededTimeMs%1000);
				
				entity->setCurrentBroadbandSpeed(10);
			} else
			{
				possible = false;
			}
		} else
		{
			possible = false;
		}
	}
	
	return possible;
}

bool ServerData::updateNetworkCurrentBroadbandSpeed(Entity* entity1, Entity* entity2, int packetWeight)
{
	bool possible = true;
	Entity* e1 = entity1;
	Entity* e2 = entity2;
	Entity* parent = getCommonParent(e1,e2);
	
	while ((e1 != parent || e2 != parent) && possible == true)
	{
		if ( packetWeight == 0 )
		{
			e1->setCurrentBroadbandSpeed(0);
			e2->setCurrentBroadbandSpeed(0);
		}
		else
		{
			possible = e1->setCurrentBroadbandSpeed(e1->getCurrentBroadbandSpeed() + packetWeight);
			possible = e2->setCurrentBroadbandSpeed(e2->getCurrentBroadbandSpeed() + packetWeight);
		}
		if (e1 != parent )
			e1 = e1->getParent();
		if (e2 != parent )
			e2 = e2->getParent();
	}
	
	return possible;
}

Entity* ServerData::getCommonParent(Entity* entity1, Entity* entity2)
{
	Entity* e1 = entity1;
	Entity* e2 = entity2;
	Entity* parent = NULL;
	
	while (e1 != NULL && parent == NULL)
	{
		while(e2 != NULL && parent == NULL)
		{
			if ( e1 == e2 )
				parent = e1;
			e2 = e2->getParent();
		}
		
		e2 = entity2;
		e1 = e1->getParent();

	}
	
	return parent;
}

void ServerData::displayEntities(map<string, Entity*>* entities, int level)
{
	unsigned int i;
	map<std::string,Entity*>::const_iterator
	mit (entities->begin()),
	mend(entities->end());
		
	for(; mit!=mend; ++mit) 
	{
		cout << string( level*3, ' ' ) << mit->first << " | " << "capacity : "<< mit->second->getNetworkCapacity()<<"  | " << "broadbandSpeed : "<< mit->second->getCurrentBroadbandSpeed();
		if (mit->second->getParent() != NULL)
			cout << "  | "<< "parent : "<< (mit->second->getParent())->getName();
					
		if (mit->second->getEntities() != NULL)
		{
			cout << endl;
			displayEntities(mit->second->getEntities(), level + 1);
		}
		if (mit->second->getType() == HOST)
		{
			for (i=0; i < (mit->second->getDeploys())->size(); i++)
			{
				if ((((*(mit->second->getDeploys()))[i]).getRefFile())->getFileManager() != NULL )
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
				if (mit->second->getType() != HOST)
					list.push_back(mit->second->getIP());
				if (mit->second->getEntities() != NULL)
					fillAddressList(mit->second, list);
			}
		} else 
			list.push_back(entity->getIP());
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

