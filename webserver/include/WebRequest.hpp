#ifndef __H__WEBREQUEST__
#define __H__WEBREQUEST__

#include <map>

class WebRequest
{
public:
	WebRequest(char* raw);
	~WebRequest();
	
	std::string getMethod();
	std::string getTarget();
	std::string getParam(std::string key);
	
private:
	std::string raw;
	std::string method;
	std::string target;
	std::map<std::string, std::string> params;
};

#endif
