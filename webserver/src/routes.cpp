#include <iostream>
#include <cstring>
#include <vector>
#include <string>

#include <mongoose.h>

#include <PolypeerServer.hpp>
#include <ServerData.hpp>
#include <routes.hpp>

using namespace std;

static const char *ajax_reply_start =
  "HTTP/1.1 200 OK\r\n"
  "Cache: no-cache\r\n"
  "Content-Type: application/x-javascript\r\n"
  "\r\n";

void get_qsvar(const struct mg_request_info *request_info,
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
	
	for (vector<File*>::iterator it = files->begin(); it != files->end(); it++) 
	{
		if ((*it)->getFileState() != F_ERROR)
		{
			FileManager* fm = (*it)->getFileManager();
			
			mg_printf(conn, "{\"id\":%i, \"name\":\"%s\", \"state\":\"%s\"}"
				, fm->getIdFile()
				, (*it)->getName().c_str()
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

void error_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"error\":\"true\"}");
}

void get_stats_route(mg_connection* conn, const mg_request_info* request_info)
{
	PolypeerServer* server = PolypeerServer::getInstance();
	ServerData& data = server->getServerData();
	
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"%s\", \"count_deployments\":%lu, \"count_hosts\":%lu}", "online", data.getDeployFiles()->size(), data.getEntities()->size());
}

void get_host_route(mg_connection* conn, const mg_request_info* request_info)
{
	char qip[32];
	
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

			mg_printf(conn, "{\"ip\":\"%s\", \"name\":\"%s\", \"state\": \"%s\", \"deployments\": ["
				, entity->getIP().c_str(), entity->getName().c_str()
				, getStringHostState(entity->getHostState()).c_str()
			);
	
			for (std::vector<DeploymentState>::iterator it = deploys->begin(); it != deploys->end(); it++) {
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
	
	get_qsvar(request_info, "id", qid, sizeof(qid));
	
	mg_printf(conn, "%s", ajax_reply_start);	
	
	if (strcmp(qid, "undefined") == 0) 
	{
		mg_printf(conn, "{\"state\":\"error\"}");	
	} 
	else
	{
	
		std::istringstream iss(qid);
		// convertir en un int
		int id;
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
	
			mg_printf(conn, "{\"id\":\"%i\", \"name\":\"%s\", \"filename\":\"%s\", \"state\":\"%s\", \"nbchunk\":%lu, \"chunksize\":%lu, \"size\":%lu, \"hosts\":["
				, id, file->getName().c_str(), fm->getFileName().c_str()
				, getStringFileState(file->getFileState()).c_str()
				, fm->getNumberChunk()
				, fm->getChunkSize(), fm->getFileSize()
			);
	
			for (vector<vector<Entity*>* >::iterator itZone = pp->begin(); itZone != pp->end(); itZone++) 
			{
				for (vector<Entity*>::iterator it = (*itZone)->begin(); it != (*itZone)->end(); it++)
				{
					mg_printf(conn, "{\"name\":\"%s\", \"ip\":\"%s\", \"state\":\"%s\", \"current\":\"%i\", \"total\":\"%lu\"}"
						, (*it)->getName().c_str(), (*it)->getIP().c_str()
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
	
			File::deleteSortedHost(pp);
	
			mg_printf(conn, "]}");
		}
	}
}

void displayEntity(mg_connection* conn, Entity* entity)
{
	if (entity->getType() == ZONE)
	{
		map<string, Entity*>* entities = entity->getEntities();
		
		mg_printf(conn, "{\"name\":\"%s\", \"type\":\"zone\", \"nc\":%i, \"cbbs\":%i, \"hosts\":[", entity->getName().c_str(), entity->getNetworkCapacity(), entity->getCurrentBroadbandSpeed());
		
		for (map<string, Entity*>::iterator it = entities->begin(); it != entities->end();) 
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
	
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "[");
	
	for (map<string, Entity*>::const_iterator it = entities->begin(); it != entities->end();) 
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

	char* pch = NULL;
	
	pch = strtok(qzones,",");
	while (pch != NULL)
	{
		vzones.push_back(string(pch));
		pch = strtok (NULL, ",");
	}
	
	File* file = new File(data.getCurrentId(), string(qname), string(qspath), string(qcpath));

	for (unsigned int i = 0; i < vzones.size(); i++) {
		file->addEntity(data.public_getEntity(vzones[i]));
	}
	
	data.addFileToAll(file);
	
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"done\"}");
}

void pause_deployments_route(mg_connection* conn, const mg_request_info* request_info)
{
	//PolypeerServer* server = PolypeerServer::getInstance();
	
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"done\"}");
}

void delete_deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	/*PolypeerServer* server = PolypeerServer::getInstance();
	
	ServerData& data = server->getServerData();
	
	*/
}

void pause_deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	// TODO
}

