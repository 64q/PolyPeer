#include <iostream>
#include <math.h>

#include <Data.hpp>
#include <Packet.hpp>
#include <includePacket.hpp>




using namespace std;





int main ()
{
	Data data;
	for(int j = 0; j < 32;j++)
		data << '0';
	for(int i = 0; i<5000000;i++)
	data<<"B";
	
	
	// écriture de la taille du paquet
	int size = data.getSize();
	cout<<"taille init = " << size<<endl;
	for (unsigned int cpt = 0; cpt < 32; cpt++)
	{
		
		if(size == 0)
		{
			break;
		}
		if( size%2 == 1)
		{
			data[31-cpt] = '1';
			size--;
		}
		else
			data[31-cpt] = '0';
		size=size/2;
		
	}


	//----------------------------
	
	//cout<<data.getString()<<endl;
	int val = 0;
	for (unsigned int cpt = 0; cpt < 32; cpt++)
	{
		if(data[31-cpt] == '1')
			val += pow(2,cpt);
	}
	cout<<"taille = "<<val<<endl;
	return 0;
}


