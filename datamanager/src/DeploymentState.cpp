#include <iostream>

#include <DeploymentState.hpp>

using namespace std;

DeploymentState::DeploymentState(const int currentIdChunk, File* file, State s):
	currentIdChunk(currentIdChunk), currentState(s)
{
	refFile = file;
}

int DeploymentState::getId() 
{ 
	return (refFile->getFileManager())->getIdFile(); 
}

