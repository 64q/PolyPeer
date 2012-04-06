#include <iostream>

#include <WebServer.hpp>
#include <Logger.hpp>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "+--------------------------------+" << endl;
	cout << "|       WebServer PolyPeer       |" << endl;
	cout << "+----------------------------(c)-+" << endl;
	cout << "Serveur intégré au projet PolyPeer" << endl;
	
	// Récupération du serveur web
	WebServer* server = WebServer::getInstance();
	
	// Lancement du serveur
	cout << "(server) Lancement du serveur sur le port 6969 ..." << endl;
	server->run();
	
	// Suppression des allocations dynamiques
	delete server;
	
	return 0;
}
