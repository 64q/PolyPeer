/**
 *
 * Serveur PolyPeer
 *
 * Fichier Main
 *
 *
 */


#include <iostream>

#include <PolypeerServer.hpp>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "+---------------------------------+" << endl;
	cout << "|         Server PolyPeer         |" << endl;
	cout << "+---------------------------------+" << endl;
	cout << "Serveur de distribution de fichiers volumineux en réseau" << endl;
	cout << "Pour les modalités d'utilisation des sources, veuillez lire" << endl;
	cout << "le fichier LICENCE, inclu dans le projet." << endl;
	
	//PolypeerServer* server = PolypeerServer::getInstance();
	
	// Lancement du serveur
	//cout << "(server) Lancement du serveur sur le port 9696." << endl;
	//cout << "(server) Lancement du WebServer sur le port 6969." << endl;
	//server->run();
	
	// Suppression des allocations dynamiques
	//delete server;

	return 0;
}
/*
int main()
{

	list<string> list;
	ServerData* sData = ServerData::getInstance();
	XMLTool* t = XMLTool::getInstance();
	sData->updateHost(string("132.34.67.10"), 23, 15);
	sData->updateHost(string("132.34.67.10"), 23, FINISH);
	
	t->public_displayTopology();
	sData->public_displayEntities();
	
	sData->public_fillAddressList("batiment_D", list);
	//Affichage de la liste
	std::list<string>::const_iterator
	lit (list.begin()),
	lend(list.end());
	for(; lit!=lend; ++lit) std::cout << *lit << ' ';
		std::cout << std::endl;
		
	//Affichage du vecteur de fichier
	vector<File*>* vFile = sData->getDeployFiles();
	vector<Entity*>* vEntity;
	Entity* entity2;
	vector<DeploymentState>* deploys;
	
	unsigned int i, j, k;
	cout << endl;
	for (i=0; i < vFile->size(); i++)
	{
		cout << "id : " << ((*vFile)[i])->getId() <<endl;
		cout << "pointeur : " << &((*vFile)[i]) << endl;
		cout << "path : " << ((*vFile)[i])->getFilePath() <<endl;
		cout << "size : " << ((*vFile)[i])->getSize() <<endl;
		cout << "chunkSize : " << ((*vFile)[i])->getChunkSize() <<endl;
		vEntity = ((*vFile)[i])->getDeploysOn();
		for (j=0; j < vEntity->size(); j++)
		{
			entity2 = (*vEntity)[j];
			cout << "     nom host : " << entity2->getName() << " | ";
			cout << "address : " << *(entity2->getIP()) << endl;
			deploys = entity2->getDeploys();
			for (k=0; k < deploys->size(); k++)
			{
				cout << "                   ipFile : " << (((*deploys)[k]).getRefFile())<< endl;
			}
		}
	}
	
	vector<Entity*>* hosts = sData->getHosts();
	for (i=0;i < hosts->size(); i++)
	{
		cout << ((*hosts)[i])->getName() << endl;
	}
	
	delete t;
	delete sData;
	
	
	return 0;
	
}*/


