include <iostream>

using namespace std;

int main()
{
	PolypeerClient* client = PolypeerClient::getInstance();
	client->start();
}
