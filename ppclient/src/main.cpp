#include <iostream>
#include <string>

#include <PolypeerClient.hpp>
#ifdef WIN32

#else
// C library
#include <signal.h>

void kill_handler(int sig);
void defineHandleStop();
#endif

bool args(int argc, char* argv[], std::string& addr, int& port, int& portServ);

using namespace std;
int main(int argc, char* argv[])
{
	// Variables interne
	string address = "255.255.255.255";
	int port = 5555;
	int portServ = 6666;
	
	// Récupération des valeurs
	if(!args(argc, argv, address, port, portServ))
		return 0;
	
	#ifdef WIN32

	#else
		// déffinition d'un catch de signal si on n'est pas sous windows
		defineHandleStop();
	#endif
	
	// Récupération de l'instance du client
	PolypeerClient* ppc = PolypeerClient::getInstance();
	
	// Config du client
	//ppc->setConfig(address, port, portServ);

	cout << "+---------------------------------+" << endl;
	cout << "|         Client PolyPeer         |" << endl;
	cout << "+---------------------------------+" << endl;
	cout << "Fichier de log : ./log/PolypeerServer.log" << endl;
	cout << "Serveur PolyPeer   : " << address<<":"<<portServ << endl;
	cout << "Port écoute client : " << port << endl;
	cout << "PID : " << getpid() << endl;
	
	// Lancement
	ppc->start();
	
	delete ppc;
	
	return 0;
}


bool args(int argc, char* argv[], std::string& addr, int& port, int& portServ)
{
	int i = 1;
	bool toReturn = true;
	while(i < argc && toReturn)
	{
		if(string(argv[i]).compare("-a") == 0)
		{
			if((i+1) < argc)
			{
				addr = string(argv[i+1]);
			} else
				toReturn = false;
		} else if(string(argv[i]).compare("-p") == 0)
		{
			if((i+1) < argc)
			{
				port = 5555;
			} else
				toReturn = false;
		}else if(string(argv[i]).compare("-ps") == 0)
		{
			if((i+1) < argc)
			{
				portServ = 6666;
			} else
				toReturn = false;
		}
		else if((string(argv[i]).compare("help") == 0) || (string(argv[i]).compare("-h") == 0))
		{
			cout << "Client Polypeer" << endl;
			cout << "Options :" << endl;
			cout << "\t-a 	: adresse du serveur PolyPeer" << endl;
			cout << "\t-p 	: port d'écoute du client" << endl;
			cout << "\t-ps 	: port d'écoute du serveur" << endl;
			cout << "\thelp	: cette aide" << endl;
			toReturn = false;
		}
		i++;
	}
	return toReturn;
}


#ifdef WIN32
#else
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

#endif

