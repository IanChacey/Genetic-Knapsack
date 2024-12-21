#pragma once
#include "Chromosome.h"
#include <cmath>
#include <numeric>
#include <algorithm>

class Population
{
public:
	Population();
	Population(vector<Chromosome> popVector);
	void calculateAvgFitness(vector<Chromosome> passedVector);
	double getAvgFitness() { return averageFitness; }
	double getMaxFitness() { return maxFitness; }
	void l2Norm();
	void selection();
	void crossover();
	void mutation();
	vector<Chromosome> getFinalPop() { return finalPopulation; }
	Chromosome getMaxFitnessChromosome() { return maxFitnessChromosome; }

private:
	//populationVector holds the initial population to be modified, selectedChromosomes holds the list of chromosomes
	//selected for reproduction, finalPopulation is the final list of chromosomes for the generation
	vector<Chromosome> populationVector, selectedChromosomes, finalPopulation;
	double averageFitness = 0, maxFitness = 0;
	//This is the chromosome from the population with the highest fitness
	Chromosome maxFitnessChromosome = new Chromosome(true);
	vector<double> l2;
	vector<bool> selectedIndex;
};

