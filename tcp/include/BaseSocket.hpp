#ifndef BASESOCKET_H
#define BASESOCKET_H

#ifdef WIN32 /* si vous êtes sous Windows */

#include <winsock2.h>
typedef int socklen_t;

#elif defined (linux) /* si vous êtes sous Linux */

#include <cstdlib>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) ::close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else /* sinon vous êtes sur une plateforme non supportée */

#error not defined for this platform

#endif

/**
 * Classe de base des sockets.
 * Ne peut pas être instancié.
**/

class BaseSocket
{
protected:

	/**
	 * Constructeur qui initialise sans connecter la socket.
	 */
	BaseSocket();

	/**
	 * Destructeur de BseSocket (ferme la socket). Fait appel à la méthode close().
	 */
	virtual ~BaseSocket();

	/**
	 * Contient l'identifient de la socket.
	 */
	int descripteur;


public:
	/**
	 * Ferme la socket proprement.
	 */
	void close();
};

#endif // BASESOCKET_H
