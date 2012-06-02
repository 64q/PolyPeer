#include <iostream>

#include <ServerSocket.hpp>

using namespace std;

int main()
{

	//Socket sock("192.168.0.14",6666);
	ServerSocket s(6666);
	cout << "en attente" << endl;
	s.accept();

	return 0;
}



















