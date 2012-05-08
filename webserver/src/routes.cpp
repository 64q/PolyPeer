#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <routes.hpp>
#include <WebServer.hpp>
#include <WebRequest.hpp>
#include <WebResponse.hpp>
#include <TinyParser.hpp>

using namespace std;

string default_route(WebRequest& request)
{
	TinyParser parser(WebServer::getInstance()->getResourcesPath() + "/default.html");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string deployment_route(WebRequest& request)
{
	TinyParser parser(WebServer::getInstance()->getResourcesPath() + "/deployment.html");
	
	parser.inject("id", request.getParam("id"));
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string server_route(WebRequest& request)
{
	TinyParser parser(WebServer::getInstance()->getResourcesPath() + "/server.html");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string stop_route(WebRequest& request)
{
	TinyParser parser(WebServer::getInstance()->getResourcesPath() + "/stop.html");
	
	// Arrêt du serveur
	WebServer::getInstance()->stop();
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string restart_route(WebRequest& request)
{
	TinyParser parser(WebServer::getInstance()->getResourcesPath() + "/restart.html");
	
	// Restart du serveur
	WebServer::getInstance()->restart();
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string deployments_route(WebRequest& request)
{
	TinyParser parser(WebServer::getInstance()->getResourcesPath() + "/deployments.html");
	
	ostringstream oss;
	
	oss << "<table>";
	oss << "<tr><th>#</th><th>Lien d'accès</th><th>Etat</th></tr>";
	oss << "<tr><td>1</td><td><a href=\"deployment?id=1\">Deploiement #1</a></td><td style=\"color: green;\">Actif</td></tr>";
	oss << "</table>";
	
	parser.inject("list", oss.str());
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string notfound_route(WebRequest& request)
{
	TinyParser parser(WebServer::getInstance()->getResourcesPath() + "/error404.html");
	
	WebResponse response(404, parser.render());
	return response.getRawData();
}

string internalerror_route(WebRequest& request)
{
	TinyParser parser(WebServer::getInstance()->getResourcesPath() + "/error500.html");
	
	WebResponse response(500, parser.render());
	return response.getRawData();
}

string debug_route(WebRequest& request)
{
	TinyParser parser(WebServer::getInstance()->getResourcesPath() + "/debug.html");

	if (WebServer::getInstance()->isDebug()) 
	{
		parser.inject("debug", "<span style=\"color: green;\">activé</span>");
		parser.inject("link", "<a href=\"/toggledebug\">Désactiver debug</a>");
	}
	else 
	{
		parser.inject("debug", "<span style=\"color: red;\">inactif</span>");
		parser.inject("link", "<a href=\"/toggledebug\">Activer debug</a>");
	}
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string toggledebug_route(WebRequest& request)
{
	WebServer::getInstance()->toggleDebug();
	return debug_route(request);
}

string resource_route(WebRequest& request)
{
	// Test de ressource
	// Ouverture du fichier de template
	ifstream file(string(WebServer::getInstance()->getResourcesPath() + request.getTarget()).c_str(), ifstream::in); 
	
	stringstream buffer;
	
	if(file)
	{      
		// copier l'intégralité du fichier dans le buffer
		buffer << file.rdbuf();
		file.close();  // on ferme le fichier
		
		return buffer.str();
	}
	else  
	{
		buffer << "impossible d'ouvrir la ressource demandée : " << request.getTarget() << ".";
		WebServer::getInstance()->getLogger().put("error", buffer.str());
		// Redirection vers page d'erreur
		return notfound_route(request);
	}
}
