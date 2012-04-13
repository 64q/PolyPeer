#include <iostream>

#include <DeploymentState.hpp>

using namespace std;

DeploymentState::DeploymentState(const int currentIdChunk, const int fileId, std::string filename):
	currentIdChunk(currentIdChunk), fileId(fileId), filename(filename)
{
	
}
