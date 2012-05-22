#include <iostream>
#include <cstring>
#include <vector>

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
	
	/*TODO
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
	char name[32], path[64], zones[1024];
	
	get_qsvar(request_info, "name", name, sizeof(name));
	get_qsvar(request_info, "path", path, sizeof(path));
	get_qsvar(request_info, "zones", zones, sizeof(zones));

	cout << "sent: " << name << ", " << path << ", " << zones << endl;
	
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"done\"}");
}
