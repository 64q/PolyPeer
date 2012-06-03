/*
 * Fichier contenant les routes pour gérer les appels clients web
 * Quentin Lebourgeois - 2012
 *
 * Le traitement est systématique :
 *
 *   Le serveur reçoit une requête, si la route match dans les routes
 *   dispos sur le webserveur, alors le callback aproprié est appelé
 *   je procède ensuite au traitement spécifique et emet une réponse
 *   sous forme de JSON généralement (sauf pour les logs).
 *
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <ctime>

#include <mongoose.h>

#include <PolypeerServer.hpp>
#include <ServerData.hpp>
#include <routes.hpp>
#include <CreateFileException.hpp>

using namespace std;

// Cette chaine de caractère permet de créer un moule de réponse
// qui sera la réponse du serveur au client web
static const char *ajax_reply_start =
  "HTTP/1.1 200 OK\r\n"
  "Cache: no-cache\r\n"
  "Content-Type: application/x-javascript\r\n"
  "\r\n";

void get_qsvar(const mg_request_info *request_info,
                      const char *name, char *dst, size_t dst_len) {
  const char *qs = request_info->query_string;
  mg_get_var(qs, strlen(qs == NULL ? "" : qs), name, dst, dst_len);
}

void deployments_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "[");

	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();
	vector<File*>* files = data.getDeployFiles();
	vector<File*>::const_iterator it = files->begin();
	
	for (; it != files->end(); ++it) 
	{
		if ((*it)->getFileState() != F_ERROR)
		{
			FileManager* fm = (*it)->getFileManager();
			
			struct tm * timeinfo;
			time_t rawtime = (time_t)((*it)->getDate());
			char buffer[80];
			time (&rawtime);
			timeinfo = localtime(&rawtime);
			strftime (buffer,80,"%c",timeinfo);
			
			mg_printf(conn, "{\"id\":%i, \"name\":\"%s\", \"date\":\"%s\", \"state\":\"%s\"}"
				, fm->getIdFile()
				, (*it)->getName().c_str()
				, buffer
				, getStringFileState((*it)->getFileState()).c_str()
			);
	
			if ((it + 1) != files->end()) 
			{
				mg_printf(conn, ",");
			}
		}
		else 
		{
			mg_printf(conn, "{\"id\":%i, \"name\":\"%s\", \"state\":\"%s\"}"
				, 0
				, (*it)->getName().c_str()
				, getStringFileState((*it)->getFileState()).c_str()
			);
		}
	}
	
	mg_printf(conn, "]");
}

void get_stats_route(mg_connection* conn, const mg_request_info* request_info)
{
	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();
	
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"%s\", \"count_deployments\":%lu}"
		, "online", data.getDeployFiles()->size()
	);
}

void get_host_route(mg_connection* conn, const mg_request_info* request_info)
{
	char qip[32];
	
	// Permet de récupérer la variable "ip" transmise par le client
	// ex: localhost:8889?ip=192.168.0.1
	get_qsvar(request_info, "ip", qip, sizeof(qip));
	
	mg_printf(conn, "%s", ajax_reply_start);
	
	if (strcmp(qip, "undefined") == 0) 
	{
		mg_printf(conn, "{\"state\":\"error\"}");	
	} 
	else
	{
		PolypeerServer* server = PolypeerServer::getInstance();
		ServerData& data = server->getServerData();
		Entity* entity = data.getHostByAddress(qip);
		
		if (entity == NULL)
		{
			mg_printf(conn, "{\"state\":\"error\"}");	
		}
		else
		{
			std::vector<DeploymentState>* deploys = entity->getDeploys();
			std::vector<DeploymentState>::iterator it = deploys->begin();
			
			mg_printf(conn, "{\"ip\":\"%s\", \"name\":\"%s\", \"state\": \"%s\", \"deployments\": ["
				, entity->getIP().c_str(), entity->getName().c_str()
				, getStringHostState(entity->getHostState()).c_str()
			);
	
			for (; it != deploys->end(); ++it) {
				File* f = it->getRefFile();
				mg_printf(conn, "{\"name\":\"%s\", \"state\":\"%s\", \"current\":\"%i\", \"total\":\"%lu\"}"
					, f->getName().c_str()
					, getStringHostDeployState(it->getCurrentState()).c_str()
					, it->getCurrentIdChunk()
					, f->getFileManager()->getNumberChunk()
				);
		
				if ((it + 1) != deploys->end()) 
				{
					mg_printf(conn, ",");
				}
			}
	
			mg_printf(conn, "]}");
		}
	}
}

void deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	char qid[16];
	int id;
	
	get_qsvar(request_info, "id", qid, sizeof(qid));
	
	mg_printf(conn, "%s", ajax_reply_start);	
	
	if (strcmp(qid, "undefined") == 0) 
	{
		mg_printf(conn, "{\"state\":\"error\"}");	
	} 
	else
	{
		istringstream iss(qid);
		iss >> id;
	
		PolypeerServer* server = PolypeerServer::getInstance();
		ServerData& data = server->getServerData();
		File* file = data.getFile(id);
		
		if (file == NULL)
		{
			mg_printf(conn, "{\"state\":\"error\"}");	
		}
		else
		{
			FileManager* fm = file->getFileManager();
			std::vector<std::vector<Entity*>* >* pp = file->getSortedHosts();
			
			// gestion affichage de la date de déploiement
			struct tm * timeinfo;
			time_t rawtime = (time_t)(file->getDate());
			char buffer[80];
			timeinfo = localtime(&rawtime);
			
			strftime (buffer,80,"%c",timeinfo);
			
			mg_printf(conn, "{\"id\":\"%i\", \"name\":\"%s\", \"date\":\"%s\", \"filename\":\"%s\", \"state\":\"%s\", \
				\"nbchunk\":%lu, \"chunksize\":%lu, \"size\":%lu, \"hosts\":["
				, id, file->getName().c_str(), buffer
				, fm->getFileName().c_str()
				, getStringFileState(file->getFileState()).c_str()
				, fm->getNumberChunk()
				, fm->getChunkSize(), fm->getFileSize()
			);
	
			for (vector<vector<Entity*>* >::const_iterator itZone = pp->begin(); itZone != pp->end(); ++itZone) 
			{
				for (vector<Entity*>::const_iterator it = (*itZone)->begin(); it != (*itZone)->end(); ++it)
				{
					mg_printf(conn, "{\"name\":\"%s\", \"ip\":\"%s\", \"host_state\":\"%s\", \"state\":\"%s\", \"current\":\"%i\", \"total\":\"%lu\"}"
						, (*it)->getName().c_str(), (*it)->getIP().c_str()
						, getStringHostState((*it)->getHostState()).c_str()
						, getStringHostDeployState((*it)->getDeploymentState(fm->getIdFile())->getCurrentState()).c_str()
						, (*it)->getDeploymentState(fm->getIdFile())->getCurrentIdChunk()
						, fm->getNumberChunk()
					);
			
					if ((it + 1) != (*itZone)->end()) 
					{
						mg_printf(conn, ",");
					}
				}
		
				if ((itZone + 1) != pp->end()) 
				{
					mg_printf(conn, ",");
				}
			}
	
			File::deleteSortedHost(pp); // Nécessaire, des allocations dynamiques sont faite lors du listing précédent
	
			mg_printf(conn, "]}");
		}
	}
}

void displayEntity(mg_connection* conn, Entity* entity)
{
	if (entity->getType() == ZONE)
	{
		map<string, Entity*>* entities = entity->getEntities();
		map<string, Entity*>::iterator it = entities->begin();
		
		mg_printf(conn, "{\"name\":\"%s\", \"type\":\"zone\", \"nc\":%i, \"cbbs\":%i, \"hosts\":["
			, entity->getName().c_str(), entity->getNetworkCapacity()
			, entity->getCurrentBroadbandSpeed()
		);
		
		for (; it != entities->end();) 
		{
			displayEntity(conn, (*it).second);
			
			if ((++it) != entities->end()) 
			{
				mg_printf(conn, ",");
			}
		}
		
		mg_printf(conn, "]}");
	}
	else
	{
		mg_printf(conn, "{\"name\":\"%s\", \"type\":\"host\", \"ip\":\"%s\", \"state\":\"%s\"}"
			, entity->getName().c_str(), entity->getIP().c_str()
			, getStringHostState(entity->getHostState()).c_str()
		);
	}
}

void network_route(mg_connection* conn, const mg_request_info* request_info)
{
	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();
	map<string, Entity*>* entities = data.getEntities();
	map<string, Entity*>::const_iterator it = entities->begin();
	
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "[");
	
	for (; it != entities->end();) 
	{
		displayEntity(conn, (*it).second);
		
		if ((++it) != entities->end()) 
		{
			mg_printf(conn, ",");
		}
	}
	
	mg_printf(conn, "]");
}

void new_deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	char qname[32], qcpath[64], qspath[64], qzones[1024];
	
	get_qsvar(request_info, "name", qname, sizeof(qname));
	get_qsvar(request_info, "cpath", qcpath, sizeof(qcpath));
	get_qsvar(request_info, "spath", qspath, sizeof(qspath));
	get_qsvar(request_info, "zones", qzones, sizeof(qzones));

	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();

	vector<string> vzones;
	
	// Découpage des zones reçues lors de l'envoi du formulaire
	char* pch = strtok(qzones,",");
	while (pch != NULL)
	{
		vzones.push_back(string(pch));
		pch = strtok (NULL, ",");
	}
	// Fin découpage
	
	mg_printf(conn, "%s", ajax_reply_start);
	
	try 
	{
		File* file = new File(data.getCurrentId() + 1, string(qname), string(qspath), string(qcpath));
		vector<string>::const_iterator it = vzones.begin();
		
		for (; it != vzones.end(); ++it) 
		{
			file->addEntity(data.public_getEntity(*it));
		}
	
		data.addFileToAll(file);
		mg_printf(conn, "{\"state\":\"done\"}");
	} 
	catch (CreateFileException e) 
	{
		mg_printf(conn, "{\"state\":\"error\"}");
	}
}

void pause_deployments_route(mg_connection* conn, const mg_request_info* request_info)
{
	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();
	
	vector<File*>* files = data.getDeployFiles();
	vector<File*>::const_iterator it = files->begin();
	
	for (; it != files->end(); it++) 
	{
		if ((*it)->getFileState() != F_ERROR && (*it)->getFileState() != F_PAUSE)
		{
			(*it)->setFileState(F_PAUSE);
		}
	}
	
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"done\"}");
}

void delete_deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	// TODO
}

void pause_deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	char qid[32];
	int id;
	
	get_qsvar(request_info, "id", qid, sizeof(qid));
	
	std::istringstream iss(qid);
	iss >> id;
	
	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();
	
	File* file = data.getFile(id);
	
	mg_printf(conn, "%s", ajax_reply_start);
	
	if (file != NULL) 
	{
		if (file->getFileState() != F_PAUSE) 
		{
			file->setFileState(F_PAUSE);
		}
		mg_printf(conn, "{\"state\":\"done\"}");
	} 
	else 
	{
		mg_printf(conn, "{\"state\":\"error\"}");
	}
}

void unpause_deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	char qid[32];
	int id;
	
	get_qsvar(request_info, "id", qid, sizeof(qid));
	
	std::istringstream iss(qid);
	iss >> id;
	
	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();
	
	File* file = data.getFile(id);
	
	mg_printf(conn, "%s", ajax_reply_start);
	
	if (file != NULL) 
	{
		if (file->getFileState() == F_PAUSE) 
		{
			file->setFileState(READY);
		}
		mg_printf(conn, "{\"state\":\"done\"}");
	} 
	else 
	{
		mg_printf(conn, "{\"state\":\"error\"}");
	}
}

void log_route(mg_connection* conn, const mg_request_info* request_info)
{
	char qlog[32];

	get_qsvar(request_info, "log", qlog, sizeof(qlog));
	
	string log = "log/";
	log += string(qlog) + ".log";
	
   ifstream fichier(log.c_str());
	
	mg_printf(conn, "%s", ajax_reply_start);
	
	if (fichier)
	{
		std::stringstream buffer;
		buffer << fichier.rdbuf();
		fichier.close();
		mg_printf(conn, "%s", buffer.str().c_str());
	}
	else
	{
		mg_printf(conn, "error");
	}
}

