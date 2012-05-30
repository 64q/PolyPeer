#include <XMLTool.hpp>
#include <ServerData.hpp>
#include <ClientData.hpp>
#include <CreateFileException.hpp>

int main()
{

	list<string> list;
	ServerData* sData = new ServerData();
	XMLTool* t = sData->getXMLTool();
	/*sData->updateHost(string("132.34.67.10"), 23, 15);
	sData->updateHost(string("132.34.67.10"), 23, HDS_FINISH);*/
	
	
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
		
	try{
		File* fileTest = new File(sData->getCurrentId()+1,"D4","file/truc2d.png", "file/truc2d.png");
		fileTest->addEntity(sData->public_getEntity("batiment_D"));
		sData->addFileToAll(fileTest);
	} catch (CreateFileException)
	{
		cout << "OPENFILEEXCEPTION" << endl;
	}
	/*sData->deleteFile(23);*/
	
	unsigned int i, j, k;
	cout << endl;
	for (i=0; i < vFile->size(); i++)
	{
			cout << "name : " << ((*vFile)[i])->getName() << endl;
		if (((*vFile)[i])->getFileState() != F_ERROR)
		{
			cout << "id : " << ((*vFile)[i])->getFileManager()->getIdFile() <<endl;
			cout << "path : " << ((*vFile)[i])->getFileManager()->getFileName() <<endl;
			cout << "size : " << ((*vFile)[i])->getFileManager()->getFileSize() <<endl;
			cout << "fileState : " << getStringFileState(((*vFile)[i])->getFileState()) << endl;
			cout << "chunkSize : " << ((*vFile)[i])->getFileManager()->getChunkSize() <<endl;
			vEntity = ((*vFile)[i])->getDeploysOn();
			if (vEntity != NULL)
			{
				for (j=0; j < vEntity->size(); j++)
				{
					entity2 = (*vEntity)[j];
					cout << "     nom host : " << entity2->getName() << " | ";
					cout << "address : " << entity2->getIP() << " | ";
					if (entity2->getParent()!=NULL)
						cout << "parent : " << (entity2->getParent())->getName() << endl;
					deploys = entity2->getDeploys();
					for (k=0; k < deploys->size(); k++)
					{
						if ((((*deploys)[k]).getRefFile())->getFileState() != F_ERROR)
						{
							cout << "                   idFile : " << ((((*deploys)[k]).getRefFile())->getFileManager()->getIdFile())<< endl;
						}
					}
				}

			}
		}
	}
	sleep(2);
	vector<Entity*>* hosts = sData->getHosts();
	for (i=0;i < hosts->size(); i++)
	{
		cout << ((*hosts)[i])->getName();
		cout << " TIME : " << ((*hosts)[i])->getTimerState() << endl;
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
	
	Entity* e1 = sData->public_getEntity("PC1");
	Entity* e2 = sData->public_getEntity("PC5");
		
	cout << "CurrentID : "<< sData->getCurrentId() << endl;
	
	sData->updateNetworkCurrentBroadbandSpeed(e1,e2,1);
	
	
	sData->public_displayEntities();
	
	delete sData;

}
