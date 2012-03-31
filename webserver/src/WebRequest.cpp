#include <iostream>
#include <cstring>
#include <map>

#include "../include/WebRequest.hpp"

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
		string key = tmp.substr(0, pos);
		string value = tmp.substr(pos + 1);
		
		this->params.insert(pair<string, string>(key, value));
		
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
	if (this->params.find(key) != this->params.end())
	{
		return this->params[key];
	}
	else
	{
		return string("undefined");
	}
}
