class DeploymentState
{
private:
	int currentIdChunk;
	int fileId;
	std::string filename;
	
public:
	DeploymentState(const int currentIdChunk, const int fileId, std::string filename);
	
	int getCurrentIdChunk() { return currentIdChunk; }
	int getFileId() { return fileId; };
	std::string getFilename() { return filename; }
};
