#include <iostream>

#include "../include/WebServer.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	// Récupération du serveur web
	WebServer* server = WebServer::getInstance();
	
	cout << "+--------------------+" << endl;
	cout << "| WebServer PolyPeer |" << endl;
	cout << "+--------------------+" << endl;
	
	// Lancement du serveur
	cout << "(server) Lancement du serveur sur le port 6969 ..." << endl;
	server->run();
	
	// Suppression des allocations dynamiques
	delete server;
	
	return 0;
}
