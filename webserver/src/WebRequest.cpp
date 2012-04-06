#include <iostream>
#include <cstring>
#include <map>

#include <WebRequest.hpp>

using namespace std;

WebRequest::WebRequest(char* raw)
{
	// Parsage de la première ligne de raw data
	char* lines = strtok(raw, "\n");
	char* pch = strtok(lines, " ");

	// Traitement de la méthode
	this->method = string(pch);
	pch = strtok(NULL, " ");
	
	// Traitement de la cible
	char* trg = strtok(pch, "?");
	this->target = string(trg);
	trg = strtok(NULL, "?");
	
	// Traitement après le ?
	char* prms = strtok(trg, "&");
	while (prms != NULL)
	{
		string tmp = string(prms);
		size_t pos = tmp.find("=");
		this->params.insert(pair<string, string>(tmp.substr(0, pos), tmp.substr(pos + 1)));
		
		prms = strtok(NULL, "&");
	}
	
	/*
	map<string, string>::iterator it;
	cout << "-- MAP --" << endl;
	for (it = this->params.begin(); it != this->params.end(); ++it)
	{
		cout << "key = " << (*it).first << ", value = " << (*it).second << endl;
	}
	cout << "----" << endl;
	*/
}

WebRequest::~WebRequest()
{

}
	
string WebRequest::getMethod()
{
	return this->method;
}

string WebRequest::getTarget()
{
	return this->target;
}

string WebRequest::getParam(string key)
{
	map<string, string>::iterator it = this->params.find(key);
	
	if (it != this->params.end())
	{
		// Fix escape de certains chars
		string& second((*it).second);
		size_t pos = second.find("%20");
		
		while (pos != string::npos) 
		{
			second.replace(pos, 3, " ");
			pos = second.find("%20", pos);
		}
		
		return second;
	}
	else
	{
		return string("undefined");
	}
}

