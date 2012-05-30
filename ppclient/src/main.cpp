#include <iostream>
// C library
#include <signal.h>

#include <PolypeerClient.hpp>

using namespace std;

void kill_handler(int sig);

void defineHandleStop();


int main()
{
	//defineHandleStop();
	PolypeerClient::getInstance()->start();
}

void defineHandleStop()
{
	// Definition du catch d'arret
	struct sigaction act, oact;
	sigaction(SIGINT,NULL,&oact);
	act.sa_handler=kill_handler;
	act.sa_mask=oact.sa_mask;
	act.sa_flags=SA_RESTART;
	sigaction(SIGINT,&act, NULL);
}

void kill_handler(int sig)
{
	cout << endl << "Interception signal d'arret(" << sig << ")..." << endl;
	PolypeerClient* client = PolypeerClient::getInstance();
	client->stop();
}



