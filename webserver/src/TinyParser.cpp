#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/TinyParser.hpp"

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
	}
}
	
void TinyParser::inject(std::string key, std::string value)
{
	this->vars.insert(pair<string, string>(key, value));
}

void TinyParser::parse()
{
	map<string, string>::iterator it;
	unsigned int pos;
	
	for (it = this->vars.begin(); it != this->vars.end(); ++it)
	{
		string pattern = "<!" + (*it).first + "!>";
		pos = this->content.find(pattern);
		
		if (pos != string::npos)
		{
			this->content.replace(pos, pattern.length(), (*it).second);
		}
	}
}

string TinyParser::render()
{
	parse();
	return this->content;
}
