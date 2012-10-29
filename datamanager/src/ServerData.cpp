#include <ServerData.hpp>
#include <PolypeerServer.hpp>


using namespace std;

ServerData::ServerData(ServerOptions* so)
{
	clientPort = so->clientPort;
	cM = new ConnectionManager(so->serverPort);
	cM->start();
	xmlTool = new XMLTool(this);
}


ServerData::~ServerData()
{
	delete cM;
	vector <string> alreadyDelete;
	deleteDeployFiles();
	deleteHosts();
	//deleteMap(this->getEntities(), &alreadyDelete);
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

Mutex* ServerData::getMutex()
{
	return &mutex_deployFiles;
}

Semaphore* ServerData::getSemaphore()
{
	return &sem_algo;
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
			// Actualiser l'état du fichier pour L'Host
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

		// Réveil de l'algo
		sem_algo.free();
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

		// Réveil de l'algo
		sem_algo.free();
	}
}


void ServerData::updateHost(string addressHost, HostState s)
{
	Entity* host = getHostByAddress(addressHost);
	if(host != NULL)
	{
		host->setHostState(s);

		// Réveil de l'algo
		sem_algo.free();
	}
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

		// Réveil de l'algo
		sem_algo.free();
	}
}

FileManager* ServerData::addFile(File* f)
{
	//Mutex qui empèche qu'il y ai un ajout de déploiement pendant que l'algorithme principale lit la liste des déploiements
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
		//Parcours des Host à ajouter dans le fichier XML
		for(i=0; i < (f->getDeploysOn())->size(); i++)
		{
			xmlTool->writeEntityIntoFile((f->getFileManager())->getIdFile(), (*(f->getDeploysOn()))[i]);
		}
	}
}

int ServerData::getCurrentId()
{
	//la récupération de l'id se fait dans le fichier XML car il peut y avoir des déploiements FINISH qui y sont présents mais non chargés en mémoire
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
	mutex_deployFiles.lock();
	
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
	
	mutex_deployFiles.unlock();
	
}

Entity* ServerData::addHost(string name, Entity* parent, int networkCapacity, string address, string mac, string mask)
{
	Entity* host = new Host(name, parent, networkCapacity, address, mac, mask);
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

bool ServerData::updateNetworkCurrentBroadbandSpeed(Entity* entity, unsigned int packetWeightInOctet)
{
	// débit client - server
	// System de calcul du débit par parcours récursif de l'arbre
	// mise en place d'un temps d'attente apres l'envoi d'un paquet
	// Voir Olivier si ca ne marche pas ;)
	
	bool possible = true;
	
	// racine de l'arbre
	if(entity != NULL)
	{
		// si on peut envoyer
		if(entity->getTimerSpeed())
		{
			possible = updateNetworkCurrentBroadbandSpeed(entity->getParent(),packetWeightInOctet);
			if(possible)
			{
				entity->calculNewTimerSpeed(packetWeightInOctet);
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

bool ServerData::updateNetworkCurrentBroadbandSpeed(Entity* entity1, Entity* entity2, unsigned int packetWeightInOctet)
{
	bool possible = true;
	Entity* e1 = entity1;
	Entity* e2 = entity2;
	Entity* parent = getCommonParent(e1,e2);
	
	
	if(parent == NULL)
	{
		// on n'a pas trouvé la relation entre les clients
		if((e1->getTimerSpeed()) && (e2->getTimerSpeed()))
		{
			e1->calculNewTimerSpeed(packetWeightInOctet);
			e2->calculNewTimerSpeed(packetWeightInOctet);
		} else
		{
			possible = false;
		}
		cout<<"impossible (topologie mal faite)"<<endl;
	} else
	{
		// ré-init au cas ou !
		e1 = entity1;
		e2 = entity2;
		// vérifier la disponibilité du débit
		while ((e1 != NULL) && (e1 != parent) && (possible))
		{
			if(!e1->getTimerSpeed())
				possible = false;
			e1 = e1->getParent();
		}
		while ((e2 != NULL) && (e2 != parent) && (possible))
		{
			if(!e2->getTimerSpeed())
				possible = false;
			e2 = e2->getParent();
		}
		
		// on prend le débit si possible
		e1 = entity1;
		e2 = entity2;
		if(possible)
		{
			while ((e1 != NULL) && (e1 != parent))
			{
				e1->calculNewTimerSpeed(packetWeightInOctet);
				e1 = e1->getParent();
			}
			while ((e2 != NULL) && (e2 != parent))
			{
				e2->calculNewTimerSpeed(packetWeightInOctet);
				e2 = e2->getParent();
			}
		}
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
			// incrémentation de e2
			e2 = e2->getParent();
		}
		// ré-init de e2
		e2 = entity2;
		// incrémentation de e1
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

