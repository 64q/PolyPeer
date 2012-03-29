/*
 * Programme de protocole réseau
 * Contient le main avec le code principal
 * @file main.c
 * @authors DAUXAIS, BISIAUX, MATRAT, LEBOURGEOIS
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "tokenring.h"


int main(int argc, char* argv[])
{
	// Sécurité de lancement, paramètres obligatoires
	if (argc < 3)
	{
		fprintf(stderr, "usage: %s ip hostname [master]\n", *argv);
		fprintf(stderr, "ip: adresse ip de l'hôte suivante.\n");
		fprintf(stderr, "hostname: votre hostname (un char).\n");
		fprintf(stderr, "master (optionnel): lancer en mode master (cf. README).\n");
		fprintf(stderr, "version 1 en mode non multiplexé.\n");
		exit(-1);
	}

	printf("Client réseau Tokenring\n");
	printf("Mode non multiplexé\n");
	printf("-----------------------\n");
	printf("Envoi des messages vers l'ip: %s\n", *(argv + 1)); 
	printf("Vous êtes l'hôte: %s\n", *(argv + 2)); 
	
	// Initialisation du client
	init(argc, argv);
	
	if(argc > 3 && strcmp(*(argv + 3), "master") == 0)
	{
		printf("Lancement en mode master.\n");
		send_token();
	}
	else
	{
		printf("Lancement en mode normal.\n");
	}
	
	// Création d'un thread qui s'occupera d'afficher les messages reçus
	pthread_t thread;
	pthread_create(&thread, NULL, listen_packet, NULL);
	
	char msg[100];
	
	// Boucle prinicpale, traitement des entrées utilisateur
	while(run)
	{
		printf("prompt> "); 
		gets(msg);
		analyse_input(msg);
	}
	
	// Fermeture des sockets et fin du programme
	close(socket_emission);
	close(socket_reception);
	
	exit(EXIT_SUCCESS);
}






