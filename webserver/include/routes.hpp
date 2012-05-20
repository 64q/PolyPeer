#ifndef __H__ROUTES__
#define __H__ROUTES__

/**
 * Fonction utile pour récupérer les données envoyées par le client
 */
static void get_qsvar(const struct mg_request_info *request_info, const char *name, char *dst, size_t dst_len);

/**
 * Route gérant l'affichage des déploiements
 */
void deployments_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour les erreurs
 */
void error_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour récupérer l'état du serveur
 */
void state_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour afficher un déploiement
 */
void deployment_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route de l'accueil
 */
void home_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour afficher la topologie du réseau
 */
void topology_route(mg_connection* conn, const mg_request_info* request_info);

/**
 * Route pour créer un déploiement
 */
void new_deployment_route(mg_connection* conn, const mg_request_info* request_info);

#endif
