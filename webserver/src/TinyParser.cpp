#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include <TinyParser.hpp>
#include <WebServer.hpp> // Nécessaire pour le WebServer Root

using namespace std;

TinyParser::TinyParser(std::string filename)
{
	// Ouverture du fichier de template
	this->file.open(filename.c_str(), ifstream::in); 

	stringstream buffer;

	if (this->file.is_open())
	{      
		// copier l'intégralité du fichier dans le buffer
		buffer << this->file.rdbuf();
		this->content = string(buffer.str());
		this->file.close();
	}
	else  
	{
		buffer << "impossible d'ouvrir le fichier de template demandé : " << filename << ".";
		WebServer::getInstance()->logger.put("error", buffer.str());
	}
}
	
void TinyParser::inject(std::string key, std::string value)
{
	this->vars.insert(pair<string, string>(key, value));
}

void TinyParser::parsePrint()
{
	map<string, string>::iterator it;
	size_t pos, start, end;
	
	// Les patterns utilisés pour un print
	string pattern = "<!# print(";
	string closure = ") #!>";
	
	pos = this->content.find(pattern);
	
	while (pos != string::npos) 
	{
		end = pos + pattern.length();
		start = this->content.find(closure, end);
		
		it  = this->vars.find(this->content.substr(end, start - end));
		
		if (it != this->vars.end()) 
		{
			this->content.replace(pos, pattern.length() + (*it).first.length() + closure.length(), (*it).second);
		}
		
		pos = this->content.find(pattern, pos + pattern.length());
	}
}

void TinyParser::parseInclude()
{
	size_t pos, start, end;
	
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
			, TinyParser(WebServer::getInstance()->getResourcesPath() + "/" + include).render()
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
