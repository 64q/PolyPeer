#include <iostream>
#include <sstream>

#include "../include/WebResponse.hpp"

using namespace std;

WebResponse::WebResponse(int code, std::string content)
{
	this->code = code;
	this->content = content;
	this->size = content.length();
}

string WebResponse::getRawData()
{
	// Définition des headers
	ostringstream oss(ostringstream::out);
	oss << "HTTP/1.0 " << this->code << " OK\n";
	oss << "Content-Type: text/html; charset=utf-8\n";
	oss << "Content-Length: " << this->size << "\n";
	oss << "Connection: close\n\n";	
	
	// Insertion du contenu
	oss << this->content.c_str();
	
	return oss.str();
}

WebResponse::~WebResponse() {}
