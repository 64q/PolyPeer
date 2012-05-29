// Class header
#include <ShareDeployment.hpp>

// STL
#include <iostream>
#include <vector>

// Project header
#include <PolypeerServer.hpp>
#include <ServerData.hpp>
#include <includePacket.hpp>


using namespace std;


ShareDeployment::ShareDeployment(PolypeerServer* pps, ServerData* sd) :
	ppServer(pps),
	sData(sd)
{

}

ShareDeployment::~ShareDeployment()
{

}

void ShareDeployment::nextStep()
{
	// liste des déploiements
	vector<File*>* files = sData->getDeployFiles();
	
	// liste temporaire des entités du déploiement
	vector<vector<Entity*>* >* entities;
	
	// Pour chaque fichier en cour de déploiement, recherche des nouvelles actions
	for (vector<File*>::iterator itFile = files->begin(); itFile != files->end(); itFile++) 
	{
		int idFile;
		
		switch((*itFile)->getFileState())
		{
			case READY:
				// passer l'état en DEPLOYMENT
				(*itFile)->setFileState(DEPLOYMENT);
				break;
				
			case DEPLOYMENT:
				// variable très utilisé
				idFile = (*itFile)->getFileManager()->getIdFile();
				// Récupération des entités concernés par ce déploiement
				entities = (*itFile)->getSortedHosts();
				
				// Repasser un host en status WAIT (pret) si il	est bloqué
				resetBreakHost(entities);	
								
				// Faire un scan du réseau pour MAJ -> envoie du paquet d'initialisation si besoin
				networkScan(entities, (*itFile));
				
				// vérifier qu'il reste des données à déployer
				if(isEnd(entities, idFile))
				{
					(*itFile)->setFileState(FINISH);
				}
				
				// Les traitements sont effectués par zone
				for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
				{
					// récupérer le maitre de zone
					Entity* entity = selectZoneMaster((*itZone), idFile);
					
					// si il n'y a pas de master, c'est qu'aucun Host n'est dispo
					if(entity != NULL)
					{
						// si il y a plus d'un host sur la zone
						if((*itZone)->size() > 1)
						{
							// On essaye de créer un deuxieme HOST pour seed
							// car le maitre est tjs pris par le serveur
							
						
							// on essaye d'envoyer sur le maitre de zone
							sendOnMaster(entity, (*itFile));
						
							// ajout du déploiement sur forme d'arbre dans la zone
							Entity* minHost = NULL;
							Entity* seedHost = NULL;
							bool isSend;
							do
							{
								// vérifier qu'un envoi est fait
								isSend = false;
								
								// récupérer l'host le moins avancé
								minHost = getMinZoneDeployment((*itZone), idFile);
								if(minHost != NULL)
								{
									// num chunk minimum pour l'host seed
									int numChunkDL = (minHost->getDeploymentState(idFile)->getCurrentIdChunk());
									// prendre l'ordi le plus complet si possible
									seedHost = getSeedZoneDeployment((*itZone), idFile, numChunkDL+1);
							
									// SendOperation
									if((seedHost != NULL) && (seedHost != minHost))
									{
										
										Chunk chunk = (*itFile)->getFileManager()->getChunk(numChunkDL);
										Packet pSOP = PacketSendOperation((minHost->getIP()), (*itFile)->getFileManager()->getIdFile(), numChunkDL);
										// gestion débit
										//if(canTakeBroadcastNetworkFromServerTo(entity, pSOP.size()))
										//{
											//cout<< "\t Envoie intra-zone : "<< (seedHost->getIP()) << " -> "<< (minHost->getIP()) <<endl;
											sData->getConnectionManager()->sendTo((seedHost->getIP()), pSOP);
											
											isSend = true;
											minHost->setHostState(DOWNLOAD);
											seedHost->setHostState(DOWNLOAD);
										//}
									}
								}
							} while(isSend);
						} else
						{
							//l'Host est seul sur la zone, il est le seul maitre
							sendOnMaster(entity, (*itFile));
						}
					} 
				}
				// désallocation
				File::deleteSortedHost(entities);
				break;
				
			case FINISH:
				break;
				
			case F_ERROR:
				break;
			case F_PAUSE:
				break;
		}
		PolypeerServer::getInstance()->multiSleep(20);
	}
}


void ShareDeployment::sendOnMaster(Entity* entity, File* file)
{
	int idFile = file->getFileManager()->getIdFile();
	if((entity->getHostState() == WAIT) && (entity->getDeploymentState(idFile)->getCurrentState() != HDS_FINISH))
	{
		Chunk chunk = file->getFileManager()->getChunk(entity->getDeploymentState(idFile)->getCurrentIdChunk());
		Packet pSC = PacketSendChunk(chunk);
		
		
		// gestion débit
		//if(canTakeBroadcastNetworkFromServerTo(entity, pSC.size()))
		//{
			//cout<< "\t Envoie sur master : " << entity->getIP() <<endl;
			sData->getConnectionManager()->sendTo((entity->getIP()), pSC);
			entity->setHostState(DOWNLOAD);
		//}
	} 

}


void ShareDeployment::resetBreakHost(vector<vector<Entity*>* >* entities)
{
	for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
	{
		for (vector<Entity*>::iterator itHost = (*itZone)->begin(); itHost != (*itZone)->end(); itHost++) 
		{
			if((*itHost)->getHostState() == DOWNLOAD)
			{
				// si on dépasse les 20 secondes en mode DOWNLOAD, il y a un pb
				if((*itHost)->getTimerState() > 20.0)
				{
					cout<<"BREAK DOWNLOAD : "<< (*itHost)->getIP() <<endl;
					(*itHost)->setHostState(WAIT);
				}
			}
		}
	}
}

void ShareDeployment::networkScan(vector<vector<Entity*>* >* entities, File* f)
{
	for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
	{
		for (vector<Entity*>::iterator itHost = (*itZone)->begin(); itHost != (*itZone)->end(); itHost++) 
		{
			// Envoie d'un packet d'initialisation avec le client
			// -> le client renvoie où il est rendu
			// -> si le fichier n'existe pas, il est créé
			if(((*itHost)->getHostState() == WAIT) && ((*itHost)->getDeploymentState(f->getFileManager()->getIdFile())->getCurrentState() == HDS_INIT))
			{
				cout<<"SEND NEWFILE to "<< (*itHost)->getIP() <<endl;
				Packet p = PacketNewFile(f->getFileManager()->getIdFile(), f->getFileManager()->getFilePath(), f->getFileManager()->getFileSize(), f->getFileManager()->getChunkSize());
				sData->getConnectionManager()->sendTo((*itHost)->getIP(), p);
				(*itHost)->setHostState(DOWNLOAD);
			}
		}
	}
}

bool ShareDeployment::isEnd(vector<vector<Entity*>* >* entities, int idFile)
{
	bool toReturn = true;
	// Pour chaque zone qui ne contiennent pas de sous zone (ou voir def zone)
	for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
	{
		for (vector<Entity*>::iterator itHost = (*itZone)->begin(); itHost != (*itZone)->end(); itHost++) 
		{
			if(((*itHost)->getHostState() == OFFLINE) || ((*itHost)->getDeploymentState(idFile)->getCurrentState() != HDS_FINISH))
				toReturn = false;
		}
	}
	return toReturn;
}


Entity* ShareDeployment::selectZoneMaster(std::vector<Entity*>* zone, int idFile)
{
	Entity* toReturn = NULL;
	for (vector<Entity*>::iterator itHost = zone->begin(); itHost != zone->end(); itHost++) 
	{
		if(((*itHost)->getHostState() != OFFLINE) && (((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH) 
			|| ((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_WAIT)))
		{	
			if(toReturn == NULL)
			{
				toReturn = (*itHost);
			} else
			{
				if((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH)
					toReturn = (*itHost);
				else if(toReturn->getDeploymentState(idFile)->getCurrentIdChunk() < (*itHost)->getDeploymentState(idFile)->getCurrentIdChunk())
					toReturn = (*itHost);
				else if((toReturn->getDeploymentState(idFile)->getCurrentIdChunk() == (*itHost)->getDeploymentState(idFile)->getCurrentIdChunk())
							&& (toReturn->getHostState() != WAIT) && ((*itHost)->getHostState() == WAIT))
				{
					// si deux host ont le meme avancement, on choisi celui qui est disponible
					toReturn = (*itHost);
				}
			}
		
			// si l'host choisi est complet, on le choisi directement
			if((toReturn != NULL) && (toReturn->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH))
				break;
		}
	}
	return toReturn;
}


Entity* ShareDeployment::getMinZoneDeployment(std::vector<Entity*>* zone, int idFile)
{
	Entity* toReturn = NULL;
	
	for (vector<Entity*>::iterator itHost = zone->begin(); itHost != zone->end(); itHost++) 
	{
		if(((*itHost)->getHostState() == WAIT) && ((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_WAIT))
		{
			if(toReturn == NULL)
				toReturn = (*itHost);
			else if(toReturn->getDeploymentState(idFile)->getCurrentIdChunk() > (*itHost)->getDeploymentState(idFile)->getCurrentIdChunk())
				toReturn = (*itHost);
		}
	}
	
	return toReturn;
}

Entity* ShareDeployment::getSeedZoneDeployment(std::vector<Entity*>* zone, int idFile, long chunkId)
{
	Entity* toReturn = NULL;
	
	for (vector<Entity*>::iterator itHost = zone->begin(); itHost != zone->end(); itHost++) 
	{
		if
		(
			((*itHost)->getHostState() == WAIT) // l'host doit etre en attente
			&& 
			(
				((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH) // Soit il a fini le dl
				|| 
				( 	// soit son dl se passe bien et est plus avancé
					((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_WAIT) 
					&& 
					((*itHost)->getDeploymentState(idFile)->getCurrentIdChunk() >= chunkId) 
				) 
			) 
		)
		{
			if(toReturn == NULL)
				toReturn = (*itHost);
			// Si on trouve un host plus avancé on le prend (ca permet de privilégier les hosts les moins avancés)
			else if(toReturn->getDeploymentState(idFile)->getCurrentIdChunk() < (*itHost)->getDeploymentState(idFile)->getCurrentIdChunk())
				toReturn = (*itHost);
		}
		if((toReturn != NULL) && (toReturn->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH))
			break;
	}
	
	return toReturn;
}





