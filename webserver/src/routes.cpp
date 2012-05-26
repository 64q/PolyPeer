#include <iostream>
#include <cstring>
#include <vector>
#include <string>

#include <mongoose.h>

/*TODO
#include <PolypeerServer.hpp>
#include <ServerData.hpp>*/
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

	/*
	PolypeerServer* server = PolypeerServer::getInstance();
	
	ServerData& data = server->getServerData();
	
	vector<File*>* files = data.getDeployFiles();
	for (vector<File*>::iterator it = files->begin(); it != files->end(); it++) {
		FileManager* fm = (*it)->getFileManager();
		mg_printf(conn, "{\"id\":%i, \"filename\":%s}", fm->getIdFile(), fm->getFileName().c_str());
		
		if (it != files->end()--) {
			mg_printf(conn, ",");
		}
	
	}*/
	
	mg_printf(conn, "]");
}

void error_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"error\":\"true\"}");
}

void get_stats_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"online\", \"count_deployments\": 3}");
}

void get_host_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"ip\":\"192.168.0.10\", \"name\":\"irc007-02\", \"state\": \"online\", \"deployments\": [{\"name\":\"test\"}]}");
}

void deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"name\":\"trololo\"}");
}

void network_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "[");
	mg_printf(conn, "{\"id\":\"1\", \"type\":\"zone\", \"name\":\"Zone1\", \"hosts\":[{\"ip\":\"192.168.0.2\", \"name\":\"irc001-01\", \"type\":\"host\", \"state\": \"online\"}]},");
	mg_printf(conn, "{\"id\":\"2\", \"name\":\"TPRESAU1\", \"type\":\"zone\", \"hosts\":[{\"ip\":\"192.168.0.12\", \"name\":\"irc002-01\", \"type\":\"host\", \"state\": \"online\"}, {\"ip\":\"192.168.0.10\", \"name\":\"irc002-03\", \"type\":\"host\",\"state\": \"offline\"}]}");
	mg_printf(conn, "]");
}

void new_deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	char qname[32], qpath[64], qzones[1024];
	
	get_qsvar(request_info, "name", qname, sizeof(qname));
	get_qsvar(request_info, "path", qpath, sizeof(qpath));
	get_qsvar(request_info, "zones", qzones, sizeof(qzones));

	cout << "sent: " << qname << ", " << qpath << ", " << qzones << endl;

	vector<string> vzones;

	char* pch = NULL;
	
	pch = strtok(qzones,",");
	while (pch != NULL)
	{
		vzones.push_back(string(pch));
		pch = strtok (NULL, ",");
	}
	
	for (unsigned int i = 0; i < vzones.size(); i++) {
		cout << "Zone = " << vzones[i] << endl;
	}
	
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"done\"}");
}

