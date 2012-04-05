/*
 * Exemple d'utilisation du logger
 */
 
#include <iostream>

#include "../include/Logger.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Test du logger" << endl;
	
	Logger logger("log/webserver.log");
	
	logger.put("notice", "a small insert was detected...");
	logger.put("error", "hacking attempt.");
	
	return 0;
}
