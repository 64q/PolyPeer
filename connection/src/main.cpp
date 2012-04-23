#include <iostream>
#include <ServerSocket.hpp>
#include <ConnectionManager.hpp>
using namespace std;

int main()
{
	ServerSocket server(5555);

	Socket* sock = server.accept();
	vector<char*> waitingMessage;
	ConnectionManager cm(&waitingMessage);
	cm.addConnection("IRC009-11",new Socket(45));


}
