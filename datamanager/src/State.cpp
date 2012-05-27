#include <iostream>
#include <string>
#include <map>

#include <State.hpp>

using namespace std;

string getStringHostState(HostState state)
{
	string result;
	
	switch (state)
	{
		case DOWNLOAD:
			result = "download";
			break;
		case WAIT:
			result = "wait";
			break;
		case OFFLINE:
			result = "offline";
			break;
		case FULL:
			result = "full";
			break;
		default:
			result = "undefined";
	}
	
	return result;
}

string getStringHostDeployState(HostDeployState state)
{
	string result;
	
	switch (state)
	{
		case HDS_DOWNLOAD:
			result = "download";
			break;
		case HDS_WAIT:
			result = "wait";
			break;
		case HDS_FINISH:
			result = "finished";
			break;
		default:
			result = "undefined";
	}
	
	return result;
}

string getStringFileState(FileState state)
{
	string result;
	
	switch (state)
	{
		case READY:
			result = "ready";
			break;
		case DEPLOYMENT:
			result = "deployment";
			break;
		case FINISH:
			result = "finished";
			break;
		case F_ERROR:
			result = "error";
			break;
		default:
			result = "undefined";
	}
	
	return result;
}

FileState getFileStateString(string stringState)
{

	map<string, FileState> fsMap;
	fsMap.insert(make_pair("ready",READY));
	fsMap.insert(make_pair("deployment",DEPLOYMENT));
	fsMap.insert(make_pair("finished",FINISH));
	fsMap.insert(make_pair("error",F_ERROR));
	
	map<string,FileState>::iterator s = fsMap.find(stringState);
	
	return s->second;
}
