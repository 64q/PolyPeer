#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

// Includes venant du C
#include <ctime>
#include <cstdlib>

#include "../include/Logger.hpp"

using namespace std;

Logger::Logger(const string& path)
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
