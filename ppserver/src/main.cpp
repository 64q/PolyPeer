/**
 *
 * Serveur PolyPeer
 *
 * Fichier Main
 *
 *
 */

// STL
#include <iostream>
#include <string>
#include <fstream>

// C library
#include <signal.h>

// Project header
#include <PolypeerServer.hpp>
#include <Logger.hpp>

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
	cout << "le fichier LICENCE, inclu dans le projet." << endl << endl;
	
	cout << "Fichier de log : ./log/PolypeerServer.log" << endl;
	cout << "Fichier de pid : ./ppserver.pid" << endl;
	
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
	file.open("ppserver.pid", fstream::trunc);
	if (file.is_open()) 
	{
		file << getpid();
		file.close();
	}
}


