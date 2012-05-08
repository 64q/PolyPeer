#include "../include/XMLTool.hpp"

int main()
{
	list<string> list;
	Entity* entity;

	XMLTool t = XMLTool("topology.xml", "deployments.xml");
	t.public_displayTopology();
	t.public_displayEntities();
	
	t.public_fillAddressList("batiment_D", list);
	//Affichage de la liste
	std::list<string>::const_iterator
	lit (list.begin()),
	lend(list.end());
	for(; lit!=lend; ++lit) std::cout << *lit << ' ';
		std::cout << std::endl;
		
	//Affichage du vecteur de fichier
	vector<File*>* vFile = t.getDeployFiles();
	vector<Entity*>* vEntity;
	Entity* entity2;
	vector<DeploymentState>* deploys;
	
	int i, j, k;
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
		
}
