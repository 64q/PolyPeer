#include <iostream>

#include <Entity.hpp>
#include <Host.hpp>

using namespace std;

Host::Host(const std::string& name, const std::string& ip):
	Entity(name), ip(ip)
{

}

void Host::addDeploymentState(const int cid, const int fid, const std::string fname)
{
	deploys.push_back(DeploymentState(cid, fid, fname));
}
	
