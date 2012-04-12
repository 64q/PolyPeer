#include <iostream>
#include <string>

#include "../include/Data.hpp"
#include "../include/Packet.hpp"

using namespace std;

int main ()
{
	Data data;

	char fin[] = "jour !";
	string tttt(" HAHAHA - !");
	
	data+='B';
	data+='o';
	data+='n';
	
	data.add (fin, 6);
	data+=tttt;

	

	//data+='\0';
	
	char *tmp = new char [data.length()];
	data.serialize (tmp);
	cout << tmp << endl;
	
	delete [] tmp;
	
	uint32_t z = 0x41;
	char a = 'a';
	char b = 'a';
	z = 0x0;
	z = b & a;
	
	cout << dec << a << " : " << z << endl;

	return 0;
}
