#include <iostream>

#include <ServerSocket.hpp>
#include <cmath>
using namespace std;

int main()
{

	ServerSocket sock(5555);
	Socket* sock2 = sock.accept();
    //while(1);
	/*
    unsigned int num=5555555;
	unsigned char data[4];

    for(int oct=0; oct < 4; oct++)
    {
    	data[oct] = (num%256);
		num/=256;

    }


	unsigned int cible = 0;
	for(int oct=0; oct < 4; oct++)
    {
    	cout <<unsigned(data[oct])*pow(256,0)<<endl;
		cible+=unsigned(data[oct])*pow(256,oct);
    }
    cout << cible<<endl;
    */
    /*
    char data[4];

    memcpy(data, &i, 4);
    int j=0;

    memcpy(&j, data, 4);

    cout << j<<endl;
*/
	return 0;
}



















