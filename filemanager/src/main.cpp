#include <iostream>
#include <fstream>
#include <string>

#include <FileManager.hpp>



using namespace std;

int main()
{


    char file1[] = "../filemanager/dossier/a.png";
    char file2[] = "./media/test.png";

    FileManager fmanager(file1, 2);

    FileManager cible(file2,fmanager.getFileSize(), fmanager.getChunkSize(), 1);

    MD5 md5;
    string tmpStr;
    ofstream file;


	int size;
	char* serializedTmp;
	cout << fmanager.getNumberChunk()<<endl;
    for(int i=0; i<fmanager.getNumberChunk() ; i++)
    {
        Chunk tmp = fmanager.getChunk(i);
        serializedTmp = tmp.serialize(size);
        Chunk tmp2(serializedTmp, size);
        if(tmp2.isIntegrate())
        {
            cible.saveChunk(tmp2);
            cout << (float(i+1)/float(fmanager.getNumberChunk()))*100<<endl;
        }
        else
        {
            cout<<"le CRC ne correspond pas!!"<<endl;
        }

    }
    
    
    
	cout<<"fichier 3"<<endl;
    FileManager cible2("test2.png",cible.getFileSize(), cible.getChunkSize(), 1);

    for(int i=0; i<cible.getNumberChunk() ; i++)
    {
        Chunk tmp = cible.getChunk(i);
        serializedTmp = tmp.serialize(size);
        Chunk tmp2(serializedTmp, size);
        if(tmp2.isIntegrate())
        {
            cible2.saveChunk(tmp2);
            cout << (float(i+1)/float(cible.getNumberChunk()))*100<<endl;
        }
        else
        {
            cout<<"le CRC ne correspond pas!!"<<endl;
        }

    }





}

