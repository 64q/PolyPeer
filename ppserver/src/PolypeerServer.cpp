// Class header
#include <PolypeerServer.hpp>

// STL
#include <iostream>

// Project header
#include <ServerData.hpp>
#include <WebServer.hpp>
#include <PacketCallback.hpp>
#include <callbackFunctionServer.hpp>


using namespace std;

PolypeerServer* PolypeerServer::instance = NULL;

PolypeerServer::PolypeerServer() :
	BaseServer("log/PolypeerServer.log")
{
	logger.setVerboseMode(true);
	logger << "Lancement du serveur Polypeer..."<<endlog;
	webserver = WebServer::getInstance();
	
	
	// initialisation du system de callBack
	// -> permet l'appel "automatique des traitement pour un paquet
	PacketCallback * pcb = PacketCallback::getPacketCallback();
	pcb->addOperation (EReady, callbackReady);
	pcb->addOperation (EChunkReceived, callbackChunkReceived);
	pcb->addOperation (EMd5Error, callbackMd5Error);
	pcb->addOperation (EDiskFull, callbackPacketDiskFull);
	pcb->addOperation (ESendOperationFinished, callbackPacketSendOperationFinished);
}

PolypeerServer::~PolypeerServer()
{

}

PolypeerServer* PolypeerServer::getInstance()
{
	if (instance == NULL)
	{
		instance = new PolypeerServer();
	}
	return instance;
}

void PolypeerServer::start()
{
	//sData = new ServerData();
	this->running = true;
	// Lancement du webserveur
	webserver->start();
	// Lancement du server
	this->run();
}

void PolypeerServer::restart()
{
	stop();
	sleep(5000);
	start();
}

void PolypeerServer::run()
{
	// propre à 'instance serveur polypeer
	PolypeerServer* server = PolypeerServer::getInstance();
	//ServerData& data = server->getServerData();
	
	// liste des déploiements - PENSER A REMETTRE CETTE VARIABLE A JOUR REGULIEREMENT
	//vector<File*>* files = data.getDeployFiles();
	
	// liste temporaire des entités du déploiement
	//vector<Entity*>* entities;
	
	cout<< "Lancement Algo de décision" << endl;
	
	while (server->running)
	{
	/*
		cout<< "DEBUT" << endl;
		// Pour chaque fichier en cour de déploiement
		for (vector<File*>::iterator itFile = files->begin(); itFile != files->end(); itFile++) 
		{
			cout<< "\t Gestion deploiement : " << (*itFile)->getFileManager()->getFileName() << endl;
			// PRETRAITEMENT
			
			//	regarder l'état d'avancement
			//		si fini faire des vérif d'état des clients suivant un timer (5min, 1h, ...)
			//		si 0%, demander la création de tous les fichiers
			//		si reprise reverifier l'etat
			
			
		
		
			// TRAITEMENT si déploiement en cour
			// Récupération des entités concernés par le déploiement
			entities = (*itFile)->getDeploysOn();
			
			// Pour chaque zone qui ne contiennent pas de sous zone (ou voir def zone)
			for (vector<Entity*>::iterator itZone = entities->begin(); itZone != entities->end(); itZone++) 
			{
				// condition pour etre une entité
				if ((*itZone)->getIP() == NULL)
				{
					cout<<"\t\t Nom zone cible : " <<  (*itZone)->getName() << endl;
					
					// Récupérer le PC le plus avancé ou le maitre de zone si l'info est sauvegardé
					cout<<"\t\t\t Nom host cible : " << endl;
					
				}
			}

		}
		
		cout<< "FIN" << endl << endl;
		*/
		sleep(2000);
		
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
		
		*/
		
		
	}
}

void PolypeerServer::stop()
{
	webserver->stop();
	this->running = false;
}

