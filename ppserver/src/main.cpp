/**
 *
 * Serveur PolyPeer
 *
 * Fichier Main
 *
 *
 */


#include <iostream>
#include <string>
#include <fstream>
// include du C
#include <signal.h>

#include <PolypeerServer.hpp>

using namespace std;

// prototype
void args(int argc, char* argv[], bool& deamon, bool& stop);
void kill_handler(int sig);
void writePid();
void defineHandleStop();

int main(int argc, char* argv[])
{
	// variables
	bool daemon = false;
	bool stop	= false;
	
	// Récupération des paramètres
	args(argc, argv, daemon, stop);
	
	// si demande d'arret sur les arguments
	if (stop)
		return 0;
	
	// programme principale
	cout << "+---------------------------------+" << endl;
	cout << "|         Server PolyPeer         |" << endl;
	cout << "+---------------------------------+" << endl;
	cout << "Serveur de distribution de fichiers volumineux en réseau" << endl;
	cout << "Pour les modalités d'utilisation des sources, veuillez lire" << endl;
	cout << "le fichier LICENCE, inclu dans le projet." << endl;
	
	cout << endl << "Fichier de log : ./log/PolypeerServer.log" << endl;
	cout << "Fichier de pid : ./PolypeerServer.pid" << endl;
	
	// pretraitement
	writePid(); // créer le fichier avec le pid du programme
	defineHandleStop();	// mise en place de l'interception d'un signal
	
	// gestion du mode demon
	if(daemon)
	{
		
	} else
	{
		PolypeerServer* server = PolypeerServer::getInstance();
		
		(server->getLogger())<< "Le main va lancer la boucle principale !"<<endlog;
		
		// Lancement du serveur
		server->start();
	
		cout << "Serveur Polypeer terminé" << endl;
	
		// Suppression des allocations dynamiques
		delete server;
	}
	
	return 0;
}



void args(int argc, char* argv[], bool& daemon, bool& stop)
{
	int i = 1;
	while(i < argc)
	{
		if(string(argv[i]).compare("--deamon") == 0)
			daemon = true;
		else if(string(argv[i]).compare("help") == 0)
		{
			cout << "Serveur Polypeer" << endl;
			cout << "Options :" << endl;
			cout << "\t--deamon : lancer en service" << endl;
			//cout << "\t--verbose : mode verbeux" << endl;
			cout << "\thelp     : cette aide" << endl;
			stop = true;
		}
		i++;
	}
}

void defineHandleStop()
{
	// Definition du catch d'arret
	struct sigaction act, oact;
	sigaction(SIGINT,NULL,&oact);
	act.sa_handler=kill_handler;
	act.sa_mask=oact.sa_mask;
	act.sa_flags=SA_RESTART;
	sigaction(SIGINT,&act, NULL);
}

void kill_handler(int sig)
{
	cout << endl << "Interception signal d'arret(" << sig << ")..." << endl;
	PolypeerServer* server = PolypeerServer::getInstance();
	server->stop();
}

void writePid()
{
	ofstream file;
	file.open("PolypeerServer.pid", fstream::trunc);
	if (file.is_open()) 
	{
		file << getpid();
		file.close();
	}
}








/*
int main()
{

	list<string> list;
	ServerData* sData = ServerData::getInstance();
	XMLTool* t = XMLTool::getInstance();
	sData->updateHost(string("132.34.67.10"), 23, 15);
	sData->updateHost(string("132.34.67.10"), 23, FINISH);
	
	t->public_displayTopology();
	sData->public_displayEntities();
	
	sData->public_fillAddressList("batiment_D", list);
	//Affichage de la liste
	std::list<string>::const_iterator
	lit (list.begin()),
	lend(list.end());
	for(; lit!=lend; ++lit) std::cout << *lit << ' ';
		std::cout << std::endl;
		
	//Affichage du vecteur de fichier
	vector<File*>* vFile = sData->getDeployFiles();
	vector<Entity*>* vEntity;
	Entity* entity2;
	vector<DeploymentState>* deploys;
	
	unsigned int i, j, k;
	cout << endl;
	for (i=0; i < vFile->size(); i++)
	{
		cout << "id : " << ((*vFile)[i])->getId() <<endl;
		cout << "pointeur : " << &((*vFile)[i]) << endl;
		cout << "path : " << ((*vFile)[i])->getFilePath() <<endl;
		cout << "size : " << ((*vFile)[i])->getSize() <<endl;
		cout << "chunkSize : " << ((*vFile)[i])->getChunkSize() <<endl;
		vEntity = ((*vFile)[i])->getDeploysOn();
		for (j=0; j < vEntity->size(); j++)
		{
			entity2 = (*vEntity)[j];
			cout << "     nom host : " << entity2->getName() << " | ";
			cout << "address : " << *(entity2->getIP()) << endl;
			deploys = entity2->getDeploys();
			for (k=0; k < deploys->size(); k++)
			{
				cout << "                   ipFile : " << (((*deploys)[k]).getRefFile())<< endl;
			}
		}
	}
	
	vector<Entity*>* hosts = sData->getHosts();
	for (i=0;i < hosts->size(); i++)
	{
		cout << ((*hosts)[i])->getName() << endl;
	}
	
	delete t;
	delete sData;
	
	
	return 0;
	
}*/


