#include <iostream>

#include <Host.hpp>

using namespace std;

Host::Host(std::string name, std::string ip):
	name(name), ip(ip)
{

}

void Host::addDeploymentState(const int cid, const int fid, const std::string fname)
{
	deploys.push_back(DeploymentState(cid, fid, fname));
}
	
