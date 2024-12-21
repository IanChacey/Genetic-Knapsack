#pragma once
#include "Population.h"

class Generation
{
public:
	Generation();
	void createNewGeneration();

private:
	//The current population
	Population currentGeneration;
	//Vector containing all of the fitness scores for checking improvement over generations
	vector<double> fitnessVector;
	//This is the chromosome that scores the highest fitness out of all generations
	Chromosome overallMaxFitnessChromosome = new Chromosome(true);
	int generationNumber = 0;
	double generationalImprovement = 2;

};

