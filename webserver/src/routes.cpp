#include <iostream>

#include <mongoose.h>

#include <routes.hpp>

using namespace std;

static const char *ajax_reply_start =
  "HTTP/1.1 200 OK\r\n"
  "Cache: no-cache\r\n"
  "Content-Type: application/x-javascript\r\n"
  "\r\n";

void deployments_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "[");
	mg_printf(conn, "{\"id\":\"1\", \"name\":\"LinuxTpAdmin1\", \"date\":\"10-05-2012 12:32\", \"state\": \"online\"},");
	mg_printf(conn, "{\"id\":\"2\", \"name\":\"LinuxTpAdmin2\", \"date\":\"10-05-2012 12:32\", \"state\": \"offline\"},");
	mg_printf(conn, "{\"id\":\"3\", \"name\":\"LinuxTpAdmin2\", \"date\":\"10-05-2012 12:32\", \"state\": \"online\"}");
	mg_printf(conn, "]");
}

void error_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"error\":\"true\"}");
}

void state_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"online\"}");
}

void deployment_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"name\":\"trololo\"}");
}

void home_route(mg_connection* conn, const mg_request_info* request_info)
{
	mg_printf(conn, "%s", ajax_reply_start);
	mg_printf(conn, "{\"state\":\"online\", \"number_deployments\": 3}");
}
