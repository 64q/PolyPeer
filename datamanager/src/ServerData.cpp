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

void ServerData::updateHost(string addressHost, int fileID, int nbChunk)
{
	Entity* host = getHostByAddress(addressHost);
	if(host != NULL)
	{
		// Actualiser le nombre de chunck pour l'host
		host->getDeploymentState(fileID)->setCurrentIdChunk(nbChunk);
		// l'host a fini son operation
		host->setHostState(WAIT);
		// Actualiser l'état du fichier POUR L'Host
		if(nbChunk >= getFile(fileID)->getFileManager()->getNumberChunk())
			host->getDeploymentState(fileID)->setCurrentState(HDS_FINISH);
		else
			host->getDeploymentState(fileID)->setCurrentState(HDS_WAIT);
	}
	
	/*unsigned int i=0;
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
	}*/
}

void ServerData::updateHost(string addressHost, int fileID, HostDeployState s)
{
	Entity* host = getHostByAddress(addressHost);
	if(host != NULL)
	{
		// l'host a fini son operation
		host->setHostState(WAIT);
		// Actualiser l'état du fichier POUR L'Host
			host->getDeploymentState(fileID)->setCurrentState(HDS_DISKFULL);
	}
/*
	unsigned int i=0;
	bool find = false;
	Entity* host = getHostByAddress(addressHost);
	vector<DeploymentState>* dState = host->getDeploys();
	
	//if ( s == HDS_DOWNLOAD)
		//host->setHostState(DOWNLOAD);
	if ( s == HDS_FINISH)
		host->setHostState(WAIT);
	
	while( (i < dState->size()) && (find == false) )
	{
		if (((*dState)[i]).getId() == fileID )
		{
			find = true;
			((*dState)[i]).setCurrentState(s);
		}
		i++;
	}*/
}


void ServerData::updateHost(string addressHost, HostState s)
{
	Entity* host = getHostByAddress(addressHost);
	if(host != NULL)
		host->setHostState(s);

	//PolypeerServer::getInstance()->getLogger() << "Un ******* a essayé de se connecter !" << endlog;
}


void ServerData::updateHostInit(string addressHost)
{
	Entity* host = getHostByAddress(addressHost);
	if(host != NULL)
	{
		host->setHostState(WAIT);
		for (vector<DeploymentState>::iterator itDeploy = host->getDeploys()->begin(); itDeploy != host->getDeploys()->end(); itDeploy++)
		{
			(*itDeploy).setCurrentState(HDS_INIT);
		}
	}
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
			i++;
		}
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

bool ServerData::updateNetworkCurrentBroadbandSpeed(Entity* entity, double packetWeight)
{
	bool possible = true;
	Entity* e = entity;
	
	if ( packetWeight == 0 )
	{
		e->setCurrentBroadbandSpeed(0);
		
	} else
	{
		while (e != NULL && possible == true)
		{
			possible = e->setCurrentBroadbandSpeed(e->getCurrentBroadbandSpeed() + packetWeight);
			e = e->getParent();
		}
	}
	
	return possible;	
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
		if (mit->second->getDeploys() != NULL)
		{
			if (!((mit->second->getDeploys())->empty()))
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

