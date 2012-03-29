/*
 * Fichier contenant les prototypes des fonctions du tokenring
 * @file tokenring.h
 * @authors DAUXAIS, BISIAUX, MATRAT, LEBOURGEOIS
 */

#ifndef _TOKEN_
#define _TOKEN_

// Port d'écoute / émission
#define UDP_PORT 6666

enum Type {
	TOKEN = 0,
	MESSAGE = 1
};
typedef enum Type Type;

/**
 * Structure globale du paquet
 */
struct Packet {
	// Contient le type du paquet
	Type type;
	// Indique la destination du packet
	char dest;
	// Indique la source du packet
	char src;
	// Message transmis
	char msg[100];
};
typedef struct Packet Packet;

static int size_of_struct = sizeof (int) + 102 * sizeof (char);

/**
 * Définition des sockets en emission & réception
 */
int socket_emission;
int socket_reception;

struct sockaddr_in addr_emission;
struct sockaddr_in addr_reception;

/**
 * Adresse ip de destination du packet à envoyer
 */
char* ip_dest;

/**
 * Variable permettant de contrôler le programme (marche/arrêt)
 */
int run;

/**
 * Contient le messsage en attente d'émission
 */
Packet waiting_packet;

/** 
 * Variable permettant de savoir si le client veut emettre ou pas
 */
static int wait_for_emission = 0;

/**
 * Contient le nom du client courant
 */
char own_name;

/**
 * Cette fonction permet d'attendre des message venant des autres hotes
 * @param void* nécessaire au fonctionnement du thread (non utilisé)
 */
void* listen_packet(void*);

/**
 * Initialise les sockets, les variables globales
 * @param int nombre d'argument de la ligne de cmd
 * @param char** les arguments de la ligne de cmd
 */
void init(int, char**);

/**
 * Permet de configurer un packet comme token
 * @param Packet* packet à configurer
 */
void create_token(Packet*);

/**
 * Permet d'envoyer un packet à l'hôte suivant
 * @param Packet* paquet à transmettre
 */
void send_packet(Packet* p);

/**
 * Créé et envoie un token sur l'hôte suivante
 */
void send_token();

/**
 * Analyse un paquet (type, dest, source) et agit en conséquence
 * @param Packet* paquet à analyser
 */
void analyse_packet(Packet *p);

/**
 * Lit le paquet et affiche le contenu du message
 * @param Packet* paquet contenant le message à afficher
 */
void read_packet(Packet* p);

/**
 * Analyse l'input utilisateur pour agit en conséquence
 * @param char* la chaine à analyser
 */
void analyse_input(char* msg);

/**
 * Créé un paquet à partir d'une adr de destination et d'un message
 * @param char la destination du message
 * @param char* le message à transmettre
 */
void create_packet(char dest, char* msg);

#endif
