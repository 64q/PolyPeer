#include <ClientData.hpp>

ClientData::ClientData(ClientOptions* co)
{
	connectionManager = new ConnectionManager(co->clientPort);
	addressServ = co->ip;
	portServ = co->serverPort;

	connectionManager->start();
}

ClientData::~ClientData()
{
	cout << "CD detruit"<<endl<<flush;
	unsigned int i;
	for (i=0;i<deploys.size();i++)
	{
		delete deploys[i];
	}
	delete connectionManager;
}

vector<FileManager*>* ClientData::getDeploys()
{
	return &deploys;
}

ConnectionManager* ClientData::getConnectionManager()
{
	return connectionManager;
}

string ClientData::getAddressServ()
{
	return addressServ;
}

int ClientData::getPortServ()
{
	return portServ;
}

void ClientData::addFileManager(FileManager* fm)
{
	deploys.push_back(fm);
}

FileManager* ClientData::getFileManager(int id)
{
	unsigned int i = 0;
	FileManager* fm = NULL;

	while (i < deploys.size() && fm == NULL)
	{
		if (deploys[i]->getIdFile() == id)
			fm = deploys[i];
		i++;
	}

	return fm;
}
