#include <iostream>
#include <string>

#include "../include/routes.hpp"
#include "../include/WebServer.hpp"
#include "../include/WebRequest.hpp"
#include "../include/WebResponse.hpp"
#include "../include/TinyParser.hpp"

using namespace std;

string default_route(WebRequest& request)
{
	TinyParser parser("webpages/default.html");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string deployment_route(WebRequest& request)
{
	TinyParser parser("webpages/deployment.html");
	
	parser.inject("deploy", request.getParam("deploy"));
	parser.inject("state", "actif");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string server_route(WebRequest& request)
{
	TinyParser parser("webpages/server.html");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string stop_route(WebRequest& request)
{
	TinyParser parser("webpages/stop.html");
	
	// Arrêt du serveur
	WebServer::getInstance()->stop();
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string restart_route(WebRequest& request)
{
	TinyParser parser("webpages/restart.html");
	
	// Restart du serveur
	WebServer::getInstance()->restart();
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string deployments_route(WebRequest& request)
{
	TinyParser parser("webpages/deployments.html");
	
	parser.inject("list", "<tr><td>Test</td><td>Value</td></tr>");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string notfound_route(WebRequest& request)
{
	TinyParser parser("webpages/error404.html");
	
	WebResponse response(404, parser.render());
	return response.getRawData();
}
