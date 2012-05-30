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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Project header
#include <PolypeerServer.hpp>
#include <Logger.hpp>

using namespace std;

// prototype
bool args(int argc, char* argv[], bool& deamon);
void kill_handler(int sig);
void defineHandleStop();
void writePid(string fileName);
bool daemon_conf ();

int main(int argc, char* argv[])
{
	// variables
	bool daemon = false;
	int pid;
	
	// Récupération des paramètres
	if (!args(argc, argv, daemon))
		return 0;
	
	// gestion du mode demon
	if(daemon)
	{
		// création d'un processus
		pid=fork();
		if (pid==-1)
		{
			cout<<"Erreur sur le fork()"<<endl;
			
		} else if (pid==0) // config du fils = daemon
		{
			// variable principale
			PolypeerServer* server = PolypeerServer::getInstance();
		
			// conf
			if(!daemon_conf ())
			{
				cout<<"Configuration du démon échoué"<<endl;
				return 0;
			}
			
			// message
			(server->getLogger())<< "Lancement du serveur Polypeer en mode démon"<<endlog;
			
			// run
			server->start();
			
			// vidage mémoire
			delete server;
			
		} else
		{
			// Quitter le père pour que le demon soit récupéré par le proces init
			return 0;
		}
	} else
	{
		// variable principale
		PolypeerServer* server = PolypeerServer::getInstance();
	
		// mise en place de l'interception d'un signal
		defineHandleStop();
		// pid du processus
		writePid("ppserver.pid");
	
		// programme principale
		cout << "+---------------------------------+" << endl;
		cout << "|         Server PolyPeer         |" << endl;
		cout << "+---------------------------------+" << endl;
		cout << "Serveur de distribution de fichiers volumineux en réseau" << endl;
		cout << "Pour les modalités d'utilisation des sources, veuillez lire" << endl;
		cout << "le fichier LICENCE, inclu dans le projet." << endl << endl;
	
		cout << "Fichier de log : ./log/PolypeerServer.log" << endl;
		cout << "Fichier de pid : ./ppserver.pid" << endl;
		cout << "PID 			: " << getpid() << endl;
		
		
		(server->getLogger())<< "Lancement du serveur Polypeer en mode normal"<<endlog;
		server->start();
	
		cout << "Serveur Polypeer terminé" << endl;
	
		// Suppression des allocations dynamiques
		delete server;
	}
	
	return 0;
}



bool args(int argc, char* argv[], bool& daemon)
{
	int i = 1;
	bool toReturn = true;
	while(i < argc)
	{
		if(string(argv[i]).compare("--daemon") == 0)
			daemon = true;
		else if((string(argv[i]).compare("help") == 0) || (string(argv[i]).compare("-h") == 0))
		{
			cout << "Serveur Polypeer" << endl;
			cout << "Options :" << endl;
			cout << "\t--daemon : lancer en service" << endl;
			//cout << "\t-wd : choisir le repertoire de travail pour le service" << endl;
			cout << "\thelp     : cette aide" << endl;
			toReturn = true;
		}
		i++;
	}
	return toReturn;
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

void writePid(string fileName)
{
	ofstream file;
	file.open(fileName.c_str(), fstream::trunc);
	if (file.is_open()) 
	{
		file << getpid();
		file.close();
	}
}


bool daemon_conf ()
{
	// change the file mode mask
	//umask (0); 
	
	// Create a new SID for the child process
	int sid = setsid ();
	if (sid < 0)
		return false;
	
	// pid du processus
	writePid("ppserver.pid");
	
	// mise en place de l'interception d'un signal
	defineHandleStop();
	
	
	// change the current working directory
	//if ((chdir("/tmp")) < 0)
	//	return false;
	
	// close out the standart file descriptor
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	close (STDERR_FILENO);
	
	return true;
}



