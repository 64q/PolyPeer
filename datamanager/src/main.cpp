#include <XMLTool.hpp>
#include <ServerData.hpp>

int main()
{
	vector<Entity*> deployOn;
	Host* h = new Host("name", NULL, 1, "123");
	deployOn.push_back(h);
	
	list<string> list;
	ServerData* sData = new ServerData();
	XMLTool* t = sData->getXMLTool();
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
	
	File* fileTest = new File(sData->getCurrentId(),"D4", "truc.png");
	fileTest->addEntity(sData->public_getEntity("batiment_D"));
	sData->addFile(fileTest);
	
	unsigned int i, j, k;
	cout << endl;
	for (i=0; i < vFile->size(); i++)
	{
		cout << "id : " << ((*vFile)[i])->getFileManager()->getIdFile() <<endl;
		cout << "name : " << ((*vFile)[i])->getName() << endl;
		cout << "pointeur : " << &((*vFile)[i]) << endl;
		cout << "path : " << ((*vFile)[i])->getFileManager()->getFileName() <<endl;
		cout << "size : " << ((*vFile)[i])->getFileManager()->getFileSize() <<endl;
		cout << "chunkSize : " << ((*vFile)[i])->getFileManager()->getChunkSize() <<endl;
		vEntity = ((*vFile)[i])->getDeploysOn();
		for (j=0; j < vEntity->size(); j++)
		{
			entity2 = (*vEntity)[j];
			cout << "     nom host : " << entity2->getName() << " | ";
			cout << "address : " << *(entity2->getIP()) << " | ";
			if (entity2->getParent()!=NULL)
				cout << "parent : " << (entity2->getParent())->getName() << endl;
			deploys = entity2->getDeploys();
			for (k=0; k < deploys->size(); k++)
			{
				cout << "                   idFile : " << ((((*deploys)[k]).getRefFile())->getFileManager()->getIdFile())<< endl;
			}
		}
	}
	
	vector<Entity*>* hosts = sData->getHosts();
	for (i=0;i < hosts->size(); i++)
	{
		cout << ((*hosts)[i])->getName() << endl;
	}
	
	/*Entity* entity10 = sData->public_getEntity("PC11");
	Entity* entity20= sData->public_getEntity("batiment_C");
	Entity* entity30 = sData->public_getEntity("PC40");
	t->writeFileIntoDeployments(32,"file/insert.txt", 12000, 1000);
	t->writeEntityIntoFile(32, entity10);
	t->writeEntityIntoFile(32, entity20);
	t->writeEntityIntoFile(32, entity30);*/
	
	/*vector<File*>* vFile2 = sData->getDeployFiles();
	unsigned int r,a,b;
	for (r=0; r < vFile2->size(); r++)
	{
		cout << "id : " << ((*vFile2)[r])->getId() <<endl;
		vector<vector<Entity*> >* vEntity = ((*vFile2)[r])->getSortedHosts();

		for(a=0; a<vEntity->size(); a++) 
		{
			cout << "      nomZone : "<< (((*vEntity)[a])[0])->getParent() << endl;
			for(b=0; b<(vEntity[a]).size(); b++)
			{
				cout << "                nomHote : "<< (((*vEntity)[a])[b])->getName() << endl;
			}
		}
	}*/
	
	cout << "CurrentID : "<< sData->getCurrentId() << endl;
	
	delete sData;
		
}
