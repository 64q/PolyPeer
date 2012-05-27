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
	/*
	Regles :
		-> une action ne doit intervenir que sur des pc en etat d'attente (dialogue entre client)
		-> prise en compte du débit très importante
		-> eviter le dialogue entre zone



		
		
		// PRETRAITEMENT
		
		//	regarder l'état d'avancement
		//		si fini faire des vérif d'état des clients suivant un timer (5min, 1h, ...)
		//		si 0%, demander la création de tous les fichiers
		//		si reprise reverifier l'etat

	*/


	// liste des déploiements
	vector<File*>* files = sData->getDeployFiles();
	
	// liste temporaire des entités du déploiement
	vector<vector<Entity*>* >* entities;
	
	
	cout<< "DEBUT" << endl;
	
	// Avant de créer de nouvelles actions (données à envoyer), on essaye de finir ce qui est en attente
	tryLaunchWaitAction();
	
	
	// Pour chaque fichier en cour de déploiement, recherche des nouvelles actions
	for (vector<File*>::iterator itFile = files->begin(); itFile != files->end(); itFile++) 
	{
		cout<< "\t Gestion deploiement : " << (*itFile)->getName() << endl;
		int idFile = (*itFile)->getFileManager()->getIdFile();
		
		// Récupération des entités concernés par ce déploiement
		entities = (*itFile)->getSortedHosts();
		
		
		switch((*itFile)->getFileState())
		{
			case READY:
				// Faire un scan du réseau pour MAJ
				cout<<"\t\t Premier passage -> MAJ du réseau" << endl;
				networkScan(entities, (*itFile));
				// passer l'état en DEPLOYMENT
				(*itFile)->setFileState(DEPLOYMENT);
				break;
				
			case DEPLOYMENT:
				
				// vérifier qu'il reste des données à déployer
				if(isEnd(entities, idFile))
				{
					(*itFile)->setFileState(FINISH);
				}
				
				cout<<"\t\t Traitement pour chaque zone" << endl;
				// Les traitements sont effectués par zone
				for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
				{
					// récupérer le maitre de zone
					Entity* entity = selectZoneMaster((*itZone), idFile);
					
					if(entity != NULL)
					{
						if((entity->getHostState() == WAIT) && (entity->getDeploymentState(idFile)->getCurrentState() != HDS_FINISH))
						{
							// envoie packet
							cout<<"\t\t\t Envoie d'un nouveau Chunk sur le maitre de zone" << endl;
							Chunk chunk = (*itFile)->getFileManager()->getChunk(entity->getDeploymentState(idFile)->getCurrentIdChunk()+1);
							Packet p = PacketSendChunk(chunk);
							// gestion débit
							//if(canTakeBroadcastNetworkFromServerTo(entity, chunk.size()))
							//{
								sData->getConnectionManager()->sendTo((entity->getIP()), p);
								//takeBroadcastNetworkFromServerTo(entity, chunk.size());
								entity->setHostState(DOWNLOAD);
							//}
						}
						
						// si il y a plus d'un host sur la zone
						if((*itZone)->size() > 1)
						{
							// ajout du déploiement sur forme d'arbre de la zone dans les actions en attentes
							cout<<"\t\t\t Déploiement intrazone" << endl;
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
											//takeBroadcastNetworkFromServerTo(entity, chunk.size());
											minHost->setHostState(DOWNLOAD);
											seedHost->setHostState(DOWNLOAD);
										//}
									}
								}
							} while(seedHost != NULL);
						}
					}
				}
			
			
				break;
				
			case FINISH:
				cout<<"\t\t FINISH"<<endl;
				break;
				
			case F_ERROR:
				cout<<"\t\t ERROR"<<endl;
				break;
			case F_PAUSE:
				cout<<"\t\t ERROR"<<endl;
				break;
		}
	}
	
	File::deleteSortedHost(entities);

	cout<< "FIN" << endl << endl;
	
}

void ShareDeployment::tryLaunchWaitAction()
{

}

bool ShareDeployment::isEnd(vector<vector<Entity*>* >* entities, int idFile)
{
	bool toReturn = true;
	// Pour chaque zone qui ne contiennent pas de sous zone (ou voir def zone)
	for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
	{
		for (vector<Entity*>::iterator itHost = (*itZone)->begin(); itHost != (*itZone)->end(); itHost++) 
		{
			if((*itHost)->getDeploymentState(idFile)->getCurrentState() != HDS_FINISH)
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
						&& (toReturn->getHostState() == WAIT) && ((*itHost)->getHostState() == WAIT))
			{
				// si deux host ont le meme avancement, on choisi celui qui est disponible
				toReturn = (*itHost);
			}
		}
		
		// si l'host choisi est complet, on le choisi directement
		if((toReturn != NULL) && (toReturn->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH))
			break;
	}
	return toReturn;
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
			
			Packet p = PacketNewFile(f->getFileManager()->getIdFile(), f->getName(), f->getFileManager()->getFileSize(), f->getFileManager()->getChunkSize());
			sData->getConnectionManager()->sendTo((*itHost)->getIP(), p);
		}
	}
}

Entity* ShareDeployment::getMinZoneDeployment(std::vector<Entity*>* zone, int idFile)
{
	Entity* toReturn = NULL;
	
	for (vector<Entity*>::iterator itHost = zone->begin(); itHost != zone->end(); itHost++) 
	{
		if( ((*itHost)->getDeploymentState(idFile)->getCurrentState() != HDS_FINISH) && ((*itHost)->getHostState() == WAIT) )
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
		if((((*itHost)->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH) || ((*itHost)->getDeploymentState(idFile)->getCurrentIdChunk() >= chunkId)) && ((*itHost)->getHostState() == WAIT))
		{
			if(toReturn == NULL)
				toReturn = (*itHost);
			else if(toReturn->getDeploymentState(idFile)->getCurrentIdChunk() < (*itHost)->getDeploymentState(idFile)->getCurrentIdChunk())
				toReturn = (*itHost);
		}
		if((toReturn != NULL) && (toReturn->getDeploymentState(idFile)->getCurrentState() == HDS_FINISH))
			break;
	}
	
	return toReturn;
}





