#ifndef __H_DEPLOYMENTSTATE__
#define __H_DEPLOYMENTSTATE__

#include <File.hpp>
#include <State.hpp>

class File;

class DeploymentState
{
	
public:
	
	DeploymentState(const int currentIdChunk, File* file, HostDeployState s);
	int getCurrentIdChunk() { return currentIdChunk; }
	int getId();
	File* getRefFile() { return refFile; }
	HostDeployState getCurrentState() { return currentState; }
	void setCurrentIdChunk(int id) { currentIdChunk = id; }
	void setCurrentState(HostDeployState s) { currentState = s; }

private:
	int currentIdChunk;
	File* refFile;
	HostDeployState currentState;
	
};


#endif
