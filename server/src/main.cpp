#include <iostream>
#include <exception>

#include <Server.hpp>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "+---------------------------------+" << endl;
	cout << "|         Server PolyPeer         |" << endl;
	cout << "+---------------------------------+" << endl;
	cout << "Serveur d'images PolyPeer" << endl;
	cout << "Pour les modalités d'utilisation des sources, veuillez lire" << endl;
	cout << "le fichier LICENSE, inclu dans le projet." << endl;
	
	Server* server = Server::getInstance();
	
	// Lancement du serveur
	cout << "(server) Lancement du serveur sur le port 9696." << endl;
	cout << "(server) Lancement du WebServer sur le port 6969." << endl;
	server->run();
	
	// Suppression des allocations dynamiques
	delete server;

	return 0;
}
