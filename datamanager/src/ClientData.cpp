#include <ClientData.hpp>

ClientData::ClientData()
{
	connectionManager = new ConnectionManager(6666);
	addressServ = "192.168.0.1";
}

ClientData::~ClientData()
{
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
