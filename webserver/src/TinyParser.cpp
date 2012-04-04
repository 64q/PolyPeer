#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "../include/TinyParser.hpp"
#include "../include/WebServer.hpp" // Nécessaire pour le WebServer Root

using namespace std;

TinyParser::TinyParser(std::string filename)
{
	// Ouverture du fichier de template
	this->file.open(filename.c_str(), ifstream::in); 

	if(this->file.is_open())
	{      
		// copier l'intégralité du fichier dans le buffer
		stringstream buffer;
		buffer << this->file.rdbuf();
		this->content = string(buffer.str());
		this->file.close();  // on ferme le fichier
	}
	else  
	{
		cerr << "Erreur, impossible d'ouvrir le fichier " << filename << "... " << endl;
		throw new std::exception;
	}
}
	
void TinyParser::inject(std::string key, std::string value)
{
	this->vars.insert(pair<string, string>(key, value));
}

void TinyParser::parsePrint()
{
	map<string, string>::iterator it;
	unsigned int pos;
	unsigned int start, end;
	string pattern = "<!# print(";
	string closure = ") #!>";
	pos = this->content.find(pattern);
	
	while (pos != string::npos) 
	{
		end = pos + pattern.length();
		start = this->content.find(closure, end);
		
		it  = this->vars.find(this->content.substr(end, start - end));
		
		if (it != this->vars.end()) {
			this->content.replace(pos, pattern.length() + (*it).first.length() + closure.length(), (*it).second);
		}
		
		pos = this->content.find(pattern, pos + pattern.length());
	}
}

void TinyParser::parseInclude()
{
	unsigned int pos;
	unsigned int start, end;
	
	// Les patterns utilisés pour un include
	string pattern = "<!# include(";
	string closure = ") #!>";
	
	pos = this->content.find(pattern);
	
	while (pos != string::npos) 
	{
		end = pos + pattern.length();
		start = this->content.find(closure, end);
		
		string include(this->content.substr(end, start - end));
	
		this->content.replace(pos
			, pattern.length() + include.length() + closure.length()
			, TinyParser(WEBSERVER_ROOT + "/" + include).render()
		);
		
		pos = this->content.find(pattern, pos + pattern.length());
	}
}

void TinyParser::parse()
{
	parsePrint();
	parseInclude();
}

string TinyParser::render()
{
	parse();
	return this->content;
}
