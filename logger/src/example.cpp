/*
 * Exemple d'utilisation du logger
 */
 
#include <iostream>

#include "../include/Logger.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Test du logger" << endl;
	
	Logger logger("log/example.log");
	
	logger.put("notice", "a small insert was detected...");
	logger.put("error", "hacking attempt.");
	
	
	// nouvelle méthode
	
	
	logger<<"sdfsdf"<<155<<12.5<<" "<<"qsdf e"<<endLog;
	logger<<error<<"Probleme de chargement"<<endLog;
	logger<<critical<<"crash du system principal"<<endLog;
	logger<<alert<<"Surcharge du serveur"<<endLog;
	
	logger.setVerboseMode(true);
	logger<<normal<<"message normal affiché grace à l'activation du verbose"<<endLog;
	logger<<"sdfsdf"<<155<<12.5<<" "<<"qsdf e"<<endLog;
	
	
	
	return 0;
}
