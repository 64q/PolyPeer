#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

// Includes venant du C
#include <ctime>
#include <cstdlib>

#include <Logger.hpp>
#include <OpenFileException.hpp>

using namespace std;

Logger::Logger(const string& path) : stringSave(""), typeSave(normal), verbose(false)
{
	this->file.open(path.c_str(), fstream::app);
	
	if (!this->file.is_open()) 
	{
		throw OpenFileException();
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

	this->file << "[" << buffer << "] [" << type << "] " << content << endl;
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
		default :
			toReturn = "undefined";
	}
	
	return toReturn;
}

