
#include <iostream>
#include "tinyxml.h"

using namespace std;

int main ()
{
	TiXmlDocument doc( "demotest.xml" );
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		cout << "prob" << endl;
	} else 
	{
		cout << "ok" << endl;
	}
	
	return 0;
}
