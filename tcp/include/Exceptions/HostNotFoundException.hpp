#include <iostream>
#include <exception>
using namespace std;

class HostNotFoundException: public exception
{

  public:
	   virtual const char* what() const throw()
	  {
		return "Impossible de trouver l'hôte";
	  }
};

