#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

#include <PolypeerClient.hpp>

/**
 * Fonction de lecture des arguments du client
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
	ClientOptions opt = {"192.168.1.88", 5555, 6666};

	// Récupération des valeurs
	int result = args(argc, argv, &opt);

	if (result == 1)
	{
		display_help(argc, argv);
		exit(0);
	}

	if (result == -1)
	{
		cout << "Erreur, les paramètres fournis sont incorrects" << endl;
		display_usage(argc, argv);
		exit(1);
	}


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


	// Lancement
	ppc->start();

	delete ppc;

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
	cout << "[-h] Affichage de l'aide" << endl;
}


