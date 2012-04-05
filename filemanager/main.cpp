

#include <iostream>
#include <fstream>

#include <string>

#include "include/md5.hpp"
#include "include/FileManager.hpp"

using namespace std;


int main()
{

    char file1[] = "a.png";
    char file2[] = "test.png";

    FileManager fmanager(file1,0, 100000);

    FileManager cible(file2,fmanager.getFileSize(), 100000);

    MD5 md5;

    for(int i=0; i<fmanager.getNumberChunk(); i++)
    {
        Chunk tmp = fmanager.getChunk(i);
        Chunk tmp2(tmp.getNumber(), tmp.getSize(), tmp.getData(),tmp.getMD5());
        if(tmp2.isIntegrate())
        {
            cible.saveChunk(tmp2);
        }
        else
        {
            cout<<"le CRC ne correspond pas!!"<<endl;
        }

    }





}
