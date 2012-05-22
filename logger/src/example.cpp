/*
 * Exemple d'utilisation du logger
 */
 
#include <iostream>

#include <Logger.hpp>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Test du logger" << endl;
	
	Logger logger("log/example.log");
	
	logger << error << "Probleme de chargement" << endlog;
	logger << critical << "Crash du system principal" <<endlog;
	logger << alert << "Surcharge du serveur" << endlog;
	
	logger.setVerboseMode(true);
	logger << normal << "Message normal affiché grace à l'activation du verbose" << endlog;
	logger << debug << "Message de debuggage" << endlog;
	logger << notice << "Information de changement d'état" << endlog;
	
	return 0;
}
