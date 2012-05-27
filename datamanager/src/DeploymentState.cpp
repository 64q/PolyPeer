#include <iostream>

#include <DeploymentState.hpp>

using namespace std;

DeploymentState::DeploymentState(const int currentIdChunk, File* file, HostDeployState s):
	currentIdChunk(currentIdChunk), currentState(s)
{
	refFile = file;
}

int DeploymentState::getId() 
{ 
	return (refFile->getFileManager())->getIdFile(); 
}

void DeploymentState::setCurrentState(HostDeployState s)
{ 
	currentState = s; 
}
