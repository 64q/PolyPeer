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
	sData(sd),
	firstLaunch(true)
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

	POUR chaque déploiement
		POUR chaque zone
			choisir un pc cible qui recoie la totalité du fichier
			si ce pc crash/s'éteind ou si c'est une reprise, choisir le pc le plus avancé dans la reception
		
			EXEMPLE :
			1)
			-> envoyer le premier chunk aux PC maitre de chaque zone
			-> chaque PC maitre envoie sur un second PC de sa zone
		
			1 bis) etape longue en client2client (se déroule sur la durée)
			-> expension du chunk sur toutes les machines de la zone 
				2->3; 
					2->4
					3->5
						2->6
						3->7
						4->8
						5->9
							...
						
			2 bis)
			-> envoyer le deuxième chunk sur le PC maitre de chaque zone

		définition d'une zone :
			groupe (>1 PC ;) de PC lié par le chemin le plus faible
			 -> important pour gérer le cas du 1 host par zone ou pour voir une zone sur une échelle plus grande
		
		
		// PRETRAITEMENT
		
		//	regarder l'état d'avancement
		//		si fini faire des vérif d'état des clients suivant un timer (5min, 1h, ...)
		//		si 0%, demander la création de tous les fichiers
		//		si reprise reverifier l'etat

	*/


	// liste des déploiements - PENSER A REMETTRE CETTE VARIABLE A JOUR REGULIEREMENT
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
		
		// Récupération des entités concernés par ce déploiement
		entities = (*itFile)->getSortedHosts();
		
		if(firstLaunch)
		{
			cout<<"\t\t Premier passage" << endl;
			// Faire un scan du réseau pour MAJ
			cout<<"\t\t\t MAJ du réseau" << endl;
			ShareDeployment::networkScan(entities, (*itFile));
			
			if(!isEnd(entities, 1))
			{
				cout<<"\t\t\t Recréer les actions en attente" << endl;
				// refaire le tableau des actions en fonction du maitre de zone
			}
		} else
		{
			// Vérifier si il y a quelque chose à faire
			if(!isEnd(entities, 1))
			{
				cout<<"\t\t Traitement pour chaque zone" << endl;
				// Les traitements sont effectués par zone
				for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
				{
					// récupérer le maitre de zone
					Entity* entity = selectZoneMaster((*itZone));
					
					if(entity != NULL)
					{
						// envoie packet
						cout<<"\t\t\t Envoie d'un nouveau Chunk sur le maitre de zone" << endl;
						
						//sData->getConnectionManager()->sendTo((*(entity->getIP())), PacketSendChunk(Chunk& chunk));
						// ajout du déploiement sur forme d'arbre de la zone dans les actions en attentes
						cout<<"\t\t\t Création de l'arbre de déploiement sous forme d'action dans la liste d'attente" << endl;
					}
				}
			}
		}
	}

	// L'état de déploiement a été mis a jour
	if(firstLaunch)
		firstLaunch=false;
		
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
			//if(deploy == FULL)
				toReturn = false;
		}
	}
	return toReturn;
}


Entity* ShareDeployment::selectZoneMaster(std::vector<Entity*>* zone)
{
	Entity* toReturn = NULL;
	for (vector<Entity*>::iterator itHost = zone->begin(); itHost != zone->end(); itHost++) 
	{
		//if((*itHost)->
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
			sData->getConnectionManager()->sendTo((*(*itHost)->getIP()), p);
		}
	}
}


/*
// Pour chaque zone qui ne contiennent pas de sous zone (ou voir def zone)
for (vector<vector<Entity*>* >::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
{
	
	for (vector<Entity*>::iterator itHost = (*itZone)->begin(); itHost != (*itZone)->end(); itHost++) 
	{
	
		cout<<"\t\t Nom zone cible : " <<  (*itHost)->getName() << endl;
	
		// Récupérer le PC le plus avancé ou le maitre de zone si l'info est sauvegardé
		//cout<<"\t\t\t Nom host cible : " << endl;
	}
}*/



