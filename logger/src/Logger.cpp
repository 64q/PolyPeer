#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

// Includes venant du C
#include <ctime>
#include <cstdlib>

#include "../include/Logger.hpp"

using namespace std;

Logger::Logger(const string& path) : stringSave(""), typeSave(normal), verbose(false)
{
	this->file.open(path.c_str(), fstream::app);
	
	if (!this->file.is_open()) 
	{
		throw new std::exception;
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

string Logger::getContent()
{
	return string("unimplemented");
}

Logger& Logger::operator<<(const ELogAction logAct)
{

	switch (logAct)
	{
		case endLog :
			if (verbose || (typeSave>normal))
			put(getType(typeSave), stringSave);
			stringSave="";
			typeSave=normal;
			break;
		case endLine :
			stringSave+="\n";
			break;
	}
	return *this;
}

Logger& Logger::operator<<(const ELogImportance logType)
{
	typeSave=logType;
	return *this;
}

string Logger::getType (const ELogImportance logType)
{
	string toReturn;
	switch (logType)
	{
		case normal :
			toReturn="normal";
			break;
		case alert :
			toReturn="ALERT";
			break;
		case error :
			toReturn="ERROR";
			break;
		case critical :
			toReturn="CRITICAL";
			break;
		default :
			toReturn="undefined";
	}
	return toReturn;
}

