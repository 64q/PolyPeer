#include <File.hpp>
#include <Zone.hpp>

File::File(int id, string path, int size, int chunkSize)
{
	/*try 
	{
		fileM = new FileManager(path.data(), (long)chunkSize, id);
	} catch (openFileException)
	{
		cout << "Fichier " << path << " inexistant"<< endl;
	}*/
	fileM= new FileManager(path.data(),(long)size, (long)chunkSize, id);
}

File::~File()
{
	delete fileM;
}

vector<vector<Entity*>* >* File::getSortedHosts()
{
	unsigned int i,j;
	vector<vector<Entity*>* >* toReturn = new vector<vector<Entity*>* >();
	
	bool find = false;
	
	for(i=0;i<deploysOn.size();i++) 
	{
		Entity* host = deploysOn[i];
		find = false;
		for (j=0;j<toReturn->size();j++)
		{
			Entity* host2 = (*(*toReturn)[j])[0];
			if (host->getParent() == host2->getParent())
			{
				((*toReturn)[j])->push_back(host);
				find = true;
			}
			
		}
		if (find == false)
		{
			toReturn->push_back(new vector<Entity*> (1,host));
		}
		
	}
	
	return toReturn;
}


void File::addEntity(Entity* entity)
{
	deploysOn.push_back(entity);
} 
