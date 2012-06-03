/*
 * Logger
 * Blin Olivier - Lebourgeois Quentin - 2012
 */

// Class header
#include <Logger.hpp>

// STL
#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

#ifdef WIN32
	#include <windows.h>
#endif

// C library
#include <ctime>
#include <cstdlib>

#include <sys/stat.h>
#include <sys/types.h>

// Project header
#include <OpenLoggerException.hpp>

using namespace std;


void createDir(string pathDirectory, string currentPath)
{
	//on découpe la chaîne par le séparateur / ou \ pour pouvoir créer dosier par dossier en caas d'imbrication
	int ind = pathDirectory.find_first_of("/\\");

	// si il y a un séparateur de dossier c'est qu'il faut en crée un
	if (ind > 0)
	{
		string tmp = currentPath + pathDirectory.substr(0,ind);
	 #ifdef WIN32
		CreateDirectory(tmp.c_str(), NULL);
	 #elif defined(linux)
	     mkdir(tmp.c_str(),S_IRWXU|S_IRWXG|S_IRWXO);
	 #endif
		createDir(pathDirectory.substr(ind+1), tmp+"/");
	}
}

Logger::Logger(const string& path) throw(OpenLoggerException) : stringSave(""), typeSave(normal), verbose(false)
{
	this->file.open(path.c_str(), fstream::app);

	if (!this->file.is_open())
	{
		createDir("./log/", "");

		this->file.open(path.c_str(), fstream::app);

		if (!this->file.is_open()) // Seconde ouverture en echec
		{
			throw OpenLoggerException();
		}
	}
}

Logger::~Logger()
{
	this->file.close();
}

void Logger::put(const string& type, const string& content)
{	
	char buffer[256];
	time_t timestamp = time(NULL);

	strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", localtime(&timestamp));
	
	
	this->file << "[" << buffer << "] [" << type << "] " << content << endl << flush;
}

Logger& Logger::operator<<(const ELogAction logAct)
{
	switch (logAct)
	{
		case endlog:
			if (verbose || (typeSave>normal))
			put(getType(typeSave), stringSave);
			stringSave = "";
			typeSave = normal;
			break;
		case endline :
			stringSave += "\n";
			break;
	}
	
	return *this;
}

Logger& Logger::operator<<(const ELogImportance logType)
{
	typeSave = logType;
	return *this;
}

string Logger::getType(const ELogImportance logType)
{
	string toReturn;

	switch (logType)
	{
		case normal:
			toReturn = "normal";
			break;
		case alert:
			toReturn = "alert";
			break;
		case error:
			toReturn = "error";
			break;
		case critical:
			toReturn = "critical";
			break;
		case debug:
			toReturn = "debug";
			break;
		case notice:
			toReturn = "notice";
			break;
		default :
			toReturn = "undefined";
	}

	return toReturn;
}

