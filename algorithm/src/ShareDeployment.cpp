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
	
	
	cout<< "DEBUT" << endl;
	
	// Pour chaque fichier en cour de déploiement, recherche des nouvelles actions
	for (vector<File*>::iterator itFile = files->begin(); itFile != files->end(); itFile++) 
	{
		cout<< "\t Gestion deploiement : " << (*itFile)->getName() << endl;
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
					cout<<"\t\t Zone :" << endl;
					// récupérer le maitre de zone
					Entity* entity = selectZoneMaster((*itZone), idFile);
					
					// si il n'y a pas de master, c'est qu'aucun Host n'est dispo
					if(entity != NULL)
					{
						cout<<"\t\t\t Maitre" << entity->getIP() << endl;
						if((entity->getHostState() == WAIT) && (entity->getDeploymentState(idFile)->getCurrentState() != HDS_FINISH))
						{
							// envoie packet
							
							Chunk chunk = (*itFile)->getFileManager()->getChunk(entity->getDeploymentState(idFile)->getCurrentIdChunk()+1);
							Packet p = PacketSendChunk(chunk);
							// gestion débit
							//if(canTakeBroadcastNetworkFromServerTo(entity, chunk.size()))
							//{
								cout<< "\t\t\t\t Envoie sur master"<<endl;
								sData->getConnectionManager()->sendTo((entity->getIP()), p);
								entity->setHostState(DOWNLOAD);
							//}
						} else
						{
							cout<<"\t\t\t\t Aucun envoi" << endl;
						}
						
						// si il y a plus d'un host sur la zone
						if((*itZone)->size() > 1)
						{
							cout<<"\t\t\t Intrazone :" << endl;
							// ajout du déploiement sur forme d'arbre de la zone dans les actions en attentes
							Entity* minHost = NULL;
							Entity* seedHost = NULL;
							do
							{
								// récupérer l'host le moins avancé
								minHost = getMinZoneDeployment((*itZone), idFile);
								if(minHost != NULL)
								{
									int numChunkDL = (minHost->getDeploymentState(idFile)->getCurrentIdChunk())+1;
									// prendre l'ordi le plus complet différent du maitre de zone si possible
									seedHost = getSeedZoneDeployment((*itZone), idFile, numChunkDL);
							
									// SendOperation
									if(seedHost != NULL)
									{
										// gestion débit
										//if(canTakeBroadcastNetworkFromServerTo(entity, chunk.size()))
										//{
											Chunk chunk = (*itFile)->getFileManager()->getChunk(numChunkDL);
											sData->getConnectionManager()->sendTo((seedHost->getIP()), PacketSendOperation((minHost->getIP()), chunk));
											cout<< "\t\t\t\t Envoie sur zone"<<endl;
											minHost->setHostState(DOWNLOAD);
											seedHost->setHostState(DOWNLOAD);
										//}
									}
								}
							} while(seedHost != NULL);
						} else
						{
							cout<< "\t\t\t\t Moins d'un host"<<endl;
						}
					} else
					{
						cout<<"\t\t\t Pas de Maitre" << endl;
					}
				}
			
				// désallocation
				File::deleteSortedHost(entities);
				break;
				
			case FINISH:
				cout<<"\t\t FINISH"<<endl;
				break;
				
			case F_ERROR:
				cout<<"\t\t ERROR"<<endl;
				break;
			case F_PAUSE:
				cout<<"\t\t PAUSE"<<endl;
				break;
		}
	}
	
	cout<< "FIN" << endl << endl;
	
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





