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
	// on prend le mutex
	sData->getMutex()->lock();
	// liste des déploiements
	vector<File*>* files = sData->getDeployFiles();
	
	// liste temporaire des entités du déploiement
	vector<vector<Entity*>* >* entities;
	
	// Pour chaque fichier en cour de déploiement, recherche des nouvelles actions
	for (vector<File*>::iterator itFile = files->begin(); itFile != files->end(); itFile++) 
	{
		// variable très utilisé
		int idFile = (*itFile)->getFileManager()->getIdFile();
		
		switch((*itFile)->getFileState())
		{
			case READY:
				// passer l'état en DEPLOYMENT
				(*itFile)->setFileState(DEPLOYMENT);
				break;
				
			case DEPLOYMENT:
				
				
				// Récupération des entités concernés par ce déploiement
				entities = (*itFile)->getSortedHosts();

				// Repasser un host en status WAIT (pret) si il	est bloqué plus d'un certain temps
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
					Entity* hostMaster = selectZoneMaster((*itZone), idFile);

					// si il n'y a pas de master, c'est qu'aucun Host n'est dispo
					if(hostMaster != NULL)
					{

						// si il y a plus d'un host sur la zone
						if((*itZone)->size() > 1)
						{
							// On essaye de créer un deuxieme HOST pour seed sur la zone
							// car le maitre est tjs pris par le serveur
							Entity* seedHostZone = NULL; //selectSeedHostOnZone((*itZone), idFile, hostMaster);

							// si on a trouver un deuxieme host pour seed la zone pendant que le master 
							// récupere le fichier du serveur
							if(seedHostZone != NULL)
							{
								sendOperationOnHosts(hostMaster, seedHostZone, (*itFile));
							}

							// on essaye d'envoyer sur le maitre de zone
							sendOnMaster(hostMaster, (*itFile));

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
									// prendre l'ordi le plus complet si possible
									seedHost = getSeedZoneDeployment((*itZone), idFile, minHost);
							
									// SendOperation
									if(seedHost != NULL)
									{
										isSend = sendOperationOnHosts(seedHost, minHost, (*itFile));
									}
								}
							} while(isSend);
						} else
						{
							// Un seul Host sur la zone, il est maitre par défaut
							sendOnMaster(hostMaster, (*itFile));
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
		PolypeerServer::getInstance()->multiSleep(4);
	}
	
	if(makePause())
		PolypeerServer::getInstance()->multiSleep(750);
	
	// On rend le mutex	
	sData->getMutex()->unlock();
}

bool ShareDeployment::makePause()
{
	bool toReturn = true;
	vector<File*>* files = sData->getDeployFiles();

	for (vector<File*>::iterator itFile = files->begin(); itFile != files->end(); itFile++) 
	{
		if(((*itFile)->getFileState() == READY) || ((*itFile)->getFileState() == DEPLOYMENT))
		{
			toReturn = false;
			break;
		}
	}
	return toReturn;
}


bool ShareDeployment::sendOnMaster(Entity* entity, File* file)
{
	bool toReturn = false;
	// sécurité
	if((entity != NULL) && (file != NULL))
	{
		// pour simplifier
		int idFile = file->getFileManager()->getIdFile();
		if((entity->getHostState() == WAIT) && (entity->getDeploymentState(idFile)->getCurrentState() != HDS_FINISH))
		{
		
			// vérif du num du chunk (dépassement)
			int numChunk = entity->getDeploymentState(idFile)->getCurrentIdChunk();
			if(numChunk <= file->getFileManager()->getNumberChunk())
			{
				// récupération du chunk
				Chunk* chunk = file->getFileManager()->getChunk(numChunk);
				
				if(chunk != NULL)
				{
					// création du paquet
					Packet pSC = PacketSendChunk((*chunk));
		
					// gestion du débit 
					// pour la taille exact du paquet on peut utiliser pSC.getSize() mais très lourd.
					// file->getFileManager()->getChunkSize()+60 donne la taille a 20 octets près
					if(sData->updateNetworkCurrentBroadbandSpeed(entity, file->getFileManager()->getChunkSize()+60))
					{
						sData->getConnectionManager()->sendTo((entity->getIP()), pSC);
						entity->setHostState(DOWNLOAD);
						toReturn = true;
					}
					
					// suppression du chunk
					delete chunk;
				}
				
			} else
			{
				// traitement erreur dépassement
				cout <<"Dépassement max chunk"<<endl;
				// on demande un nouveau paquet
				entity->getDeploymentState(idFile)->setCurrentState(HDS_INIT);
			}
		}
	}
	return toReturn;
}

bool ShareDeployment::sendOperationOnHosts(Entity* entitySrc, Entity* entityDst, File* file)
{
	bool toReturn = false;
	// sécurité
	if((entitySrc != NULL) && (entityDst != NULL) && (file != NULL))
	{
		// pour simplifier
		int idFile = file->getFileManager()->getIdFile();
		if((entitySrc->getHostState() == WAIT) && (entityDst->getHostState() == WAIT) 
			&& (entityDst->getDeploymentState(idFile)->getCurrentState() != HDS_FINISH))
		{
			// Récupérer le chunk dont l'Host de destination a besoin
			int numNeededChunk = entityDst->getDeploymentState(idFile)->getCurrentIdChunk();
			// vérif du num du chunk (dépassement)
			if(numNeededChunk <= file->getFileManager()->getNumberChunk())
			{
				// création du paquet
				Packet pSOP = PacketSendOperation(entityDst->getIP(), idFile, numNeededChunk);
				
				// gestion du débit on connait la taille du chunk mais pas la taille exact du paquet
				if(sData->updateNetworkCurrentBroadbandSpeed(entitySrc, entityDst, file->getFileManager()->getChunkSize()+60))
				{
					sData->getConnectionManager()->sendTo(entitySrc->getIP(), pSOP);
					entitySrc->setHostState(DOWNLOAD);
					entityDst->setHostState(DOWNLOAD);
					toReturn = true;
				}
			} else
			{
				// traitement erreur dépassement
				cout <<"Dépassement max chunk"<<endl;
				// on demande un nouveau paquet
				entityDst->getDeploymentState(idFile)->setCurrentState(HDS_INIT);
			}
		}
	}
	return toReturn;
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
				if((*itHost)->getTimerState() > 5.0)
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
				Packet p = PacketNewFile(f->getFileManager()->getIdFile(), f->getClientPath(), f->getFileManager()->getFileSize(), f->getFileManager()->getChunkSize());
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


Entity* ShareDeployment::selectZoneMaster(std::vector<Entity*>* zone, int idFile, Entity* forbidenHost)
{
	Entity* toReturn = NULL;
	for (vector<Entity*>::iterator itHost = zone->begin(); itHost != zone->end(); itHost++) 
	{
		if(((*itHost)->getHostState() != OFFLINE)
			&& ((*itHost) != forbidenHost)
			&& (((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH) 
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


Entity* ShareDeployment::selectSeedHostOnZone(std::vector<Entity*>* zone, int idFile, Entity* hostMaster)
{
	Entity* toReturn = NULL;

	// chercher un deuxieme master pour la zone
	Entity* secondMaster = selectZoneMaster(zone, idFile, hostMaster);
	if((hostMaster != NULL) && (secondMaster != NULL))
	{
		if(secondMaster->getDeploymentState(idFile)->getCurrentIdChunk() < (hostMaster->getDeploymentState(idFile)->getCurrentIdChunk()-1))
			toReturn = secondMaster;
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

Entity* ShareDeployment::getSeedZoneDeployment(std::vector<Entity*>* zone, int idFile, Entity* minHost)
{
	Entity* toReturn = NULL;
	
	for (vector<Entity*>::iterator itHost = zone->begin(); itHost != zone->end(); itHost++) 
	{
		if
		(
			((*itHost)->getHostState() == WAIT) // l'host doit etre en attente
			&&
			((*itHost) != minHost) // l'host doit etre en attente
			&&
			(
				((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH) // Soit il a fini le dl
				|| 
				( 	// soit son dl se passe bien et est plus avancé
					((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_WAIT) 
					&& 
					((*itHost)->getDeploymentState(idFile)->getCurrentIdChunk() > minHost->getDeploymentState(idFile)->getCurrentIdChunk()) 
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





