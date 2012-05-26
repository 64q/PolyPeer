#ifndef DEPLOYMENTALGORITHM_H
#define DEPLOYMENTALGORITHM_H

/*
 * Classe DeploymentAlgorithm
 *
 * Cette class est l'interface pour créer des algorithmes de déploiement
 *
 * par Olivier
 */



class DeploymentAlgorithm
{
public:
	DeploymentAlgorithm();
	~DeploymentAlgorithm();
	
	virtual void nextStep() = 0;
	
};


#endif //DEPLOYMENTALGORITHM_H

