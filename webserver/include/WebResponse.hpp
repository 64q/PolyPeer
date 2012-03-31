#ifndef __H__WEBRESPONSE__
#define __H__WEBRESPONSE__

class WebResponse
{
public:
	WebResponse(std::string raw);
	~WebResponse();
	
private:
	std::string raw;
};

#endif
