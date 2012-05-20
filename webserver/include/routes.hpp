#ifndef __H__ROUTES__
#define __H__ROUTES__

void deployments_route(mg_connection* conn, const mg_request_info* request_info);

void error_route(mg_connection* conn, const mg_request_info* request_info);

void state_route(mg_connection* conn, const mg_request_info* request_info);

void deployment_route(mg_connection* conn, const mg_request_info* request_info);

void home_route(mg_connection* conn, const mg_request_info* request_info);

#endif
