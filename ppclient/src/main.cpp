/*
 * Main du client
 * Olivier Blin - Matrat Erwan - Quentin Lebourgeois - 2012
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

#include <PolypeerClient.hpp>


// C library
#include <signal.h>

void kill_handler(int sig);
void defineHandleStop();
bool daemon_conf(std::string& root);
void writePid(std::string fileName);

/**
 * Fonction de lecture des arguments du client
 * @return int
 * 	0 = lancement normal
 * 	1 = lancement de l'aide
 * 	2 = lancement en démon
 */
int args(int argc, char* argv[], ClientOptions* opt);

/**
 * Affichage l'utilisation de l'executable
 */
void display_usage(int argc, char* argv[]);

/**
 * Affiche l'aide de l'executable
 */
void display_help(int argc, char* argv[]);

using namespace std;

int main(int argc, char* argv[])
{
	// Options client par défaut
	ClientOptions opt = {"192.168.0.14", 5555, 6666, false, "/tmp"};

	// Récupération des valeurs
	int result = args(argc, argv, &opt);
	int pid;
	
	if (result == 0)
	{
		// déffinition d'un catch de signal si on n'est pas sous windows
		defineHandleStop();

		// Récupération de l'instance du client
		PolypeerClient* ppc = PolypeerClient::getInstance();

		// Config du client
		ppc->setConfig(&opt);

		cout << "+---------------------------------+" << endl;
		cout << "|         Client PolyPeer         |" << endl;
		cout << "+---------------------------------+" << endl;
		cout << "Fichier de log     : log/client.log" << endl;
		cout << "Serveur PolyPeer   : " << opt.ip << ":" << opt.serverPort << endl;
		cout << "Port écoute client : " << opt.clientPort << endl;
		cout << "PID             : " << getpid() << endl;

		// Lancement
		ppc->start();
		
		delete ppc;
	}
	else if (result == 1)
	{
		display_help(argc, argv);
		exit(0);
	}
	else if (result == 2)
	{
		// mise en place de l'interception d'un signal
		defineHandleStop();
		// création d'un processus
		pid = fork();
		if (pid == -1)
		{
			cout << "Erreur, impossible de fork()" << endl;
			exit(1);
			
		}
		else if (pid == 0)
		{
			// Récupération de l'instance du client
			PolypeerClient* ppc = PolypeerClient::getInstance();
	
			if (!daemon_conf(opt.root)) // Configuration du démon
			{
				cout << "Erreur, configuration du démon échoué" <<endl;
				exit(1);
			}
		
			(ppc->getLogger())<< "Lancement du serveur Polypeer en mode démon" << endlog;
			// Config du client
			ppc->setConfig(&opt);
			// Lancement
			ppc->start();
		
			// vidage mémoire
			delete ppc;
		}
		else
		{
			exit(0); // terminaison du père pour que le fils soit récupéré par init
		}
	}	
	else
	{
		display_usage(argc, argv);
		exit(1);
	}
	

	return 0;
}

int args(int argc, char* argv[], ClientOptions* opt)
{
	int result = 0, i = 1;

	while (i < argc)
	{
		if (strcmp("-h", *(argv + i)) == 0)
		{
			result = 1;
		}
		else if (strcmp("-d", *(argv + i)) == 0)
		{
			opt->daemon = true;
			result = 2;
		}
		else
		{
			// Lecture d'un paramètre avec argument (ex : "-p 3128")
			if ((i + 1) < argc)
			{
				istringstream iss(*(argv + i + 1));

				if (strcmp("-c", *(argv + i)) == 0)
				{
					iss >> opt->clientPort;
				}
				else if (strcmp("-p", *(argv + i)) == 0)
				{
					iss >> opt->serverPort;
				}
				else if (strcmp("-s", *(argv + i)) == 0)
				{
					iss >> opt->ip;
				}
				// directory de chroot
				else if (strcmp("-r", *(argv + i)) == 0) 
				{
					opt->root = string(*(argv + i + 1));
				}
				
				i++;
			}
		}

		i++;
	}

	return result;
}

void display_usage(int argc, char* argv[])
{
	cout << "Usage: " << *argv << " [-h] [-p serverPort] [-c clientPort] [-s serverIp]" << endl;
}

void display_help(int argc, char* argv[])
{
	cout << "Aide: " << *argv << ", client PolyPeer" << endl;
	cout << "[-p serverPort] Port du serveur" << endl;
	cout << "[-c clientPort] Port du client" << endl;
	cout << "[-s serverIp] Adresse ip du serveur" << endl;
	cout << "[-d] lancer en démon" << endl;
	cout << "[-r] repertoire de chdir pour le demon" << endl;
	cout << "[-h] Affichage de l'aide" << endl;
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
	PolypeerClient* client = PolypeerClient::getInstance();
	client->stop();
}

bool daemon_conf (string& root)
{
	// change the file mode mask
	//umask (0); 
	
	// Create a new SID for the child process
	int sid = setsid ();
	if (sid < 0)
		return false;
	
	// pid du processus
	writePid("ppclient.pid");
	
	// mise en place de l'interception d'un signal
	defineHandleStop();
	
	
	// change the current working directory
	if ((chdir(root.c_str())) < 0)
		return false;
	
	// close out the standart file descriptor
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	close (STDERR_FILENO);
	
	return true;
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


