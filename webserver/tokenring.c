/*
 * Fichier contenant les fonctions nécessaire au fonctionnement
 * du tokenring
 * @file tokenring.c
 * @authors DAUXAIS, BISIAUX, MATRAT, LEBOURGEOIS
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#include "tokenring.h"

// Analyse du paquet
void analyse_packet(Packet *p)
{
	switch (p->type)
	{
		// Cas où c'est un jeton
		case TOKEN:
			// Cas où le client veut emettre
			if (wait_for_emission == 1)
			{
				send_packet(&waiting_packet);
				wait_for_emission = 0;
			}
			// Sinon on réémet simplement le jeton au suivant
			else
			{
				send_token();
			}
		break;
		default:
			// Si c'est un paquet qui nous est destiné
			if (p->dest == own_name)
			{
				read_packet(p);
				send_token();
			}
			else
			{
				// Si le paquet provient de chez nous, on renvoit un token
				if (p->src == own_name)
				{
					send_token();
				}
				else
				{
					send_packet(p);
				}
			}
		break;
	}

}

// Envoi du token
void send_token()
{
	Packet tmp;
	create_token(&tmp);
	send_packet(&tmp);
}

// Envoi du packet
void send_packet(Packet* p)
{
	sendto(socket_emission, p,size_of_struct , 0, (struct sockaddr*) & addr_emission, sizeof(struct sockaddr));
}

// Création du token
void create_token(Packet* packet)
{
	packet->type = TOKEN;
	packet->dest = -1;
	packet->src = -1;
	//packet->msg = "";
}

// Init du client
void init(int argc, char** argv)
{
	socket_emission = socket(PF_INET, SOCK_DGRAM, 0);
	socket_reception = socket(PF_INET, SOCK_DGRAM, 0);
	perror("socket: ");
	
	// Init du sockaddr d'émission
	bzero((char*) &addr_emission, sizeof(addr_emission));
	addr_emission.sin_family = AF_INET;
	addr_emission.sin_addr.s_addr = inet_addr(*(argv + 1));
	addr_emission.sin_port = htons(UDP_PORT);
	
	// Init du sockaddr de réception
	bzero((char*) &addr_reception, sizeof(addr_reception));
	addr_reception.sin_family = AF_INET;
	addr_reception.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_reception.sin_port = htons(UDP_PORT);
	
	// Binding
	bind(socket_reception, (struct sockaddr*) &addr_reception, sizeof(struct sockaddr));
	perror("bind: ");
	
	// Initialisation des globales
	wait_for_emission = 0;
	ip_dest = *(argv + 1);
	own_name = *(argv+2)[0];
	run = 1;
}

// Ecoute des packets recus
void* listen_packet(void* truc)
{
	unsigned int size_of_sock =  sizeof(struct sockaddr);
	Packet p;
	
	while(1)
	{
		recvfrom(socket_reception, &p, sizeof(Packet), 0, (struct sockaddr*) &addr_reception, &size_of_sock);
		analyse_packet(&p);
	}
}

// Lecture du paquet
void read_packet(Packet* p)
{
	printf("\n#MSG de %c: %s\n", p->src, p->msg);
}

// Analyse de l'entrée utilisateur
void analyse_input(char* msg)
{
	char message[100];
	char cmd[10];
	char hote;
	sscanf(msg,"%s %c", cmd, &hote);
	int i = strlen(cmd) + 3;
	int j = 0;
	
	while (i < strlen(msg) && msg[i] != '\0')
	{
		message[j] = msg[i];
		i++;
		j++;
	}
	message[j] = msg[i];
	
	if (strcmp(cmd, "send") == 0)
	{ // Cas de l'envoi d'un message à un hôte
		create_packet(hote, message);
	}
	else
	{
		if (strcmp(cmd, "exit") == 0)
		{ // Cas de fermeture du client
			run = 0;
			printf("#EXIT fermeture du programme...\n");
		}
	}
}

// Création du paquet
void create_packet(char dest, char* msg)
{
	// Définition des paramètres du paquet
	waiting_packet.type = MESSAGE;
	waiting_packet.dest = dest;
	waiting_packet.src = own_name;
	// Copie du message
	strcpy(waiting_packet.msg, msg);
	// Demande d'émission enclenchée
	wait_for_emission = 1;
}








