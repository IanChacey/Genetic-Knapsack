#include "Population.h"

//Constructor for the initial population
Population::Population()
{
	//Create a population of 1000 chromosomes
	for (int i = 0; i < 1000; i++)
	{
		Chromosome tempSelect;
		populationVector.push_back(tempSelect);
		selectedIndex.push_back(false);
	}

	sort(populationVector.begin(), populationVector.end());

	calculateAvgFitness(populationVector);
	l2Norm();
	selection();
	crossover();
	mutation();
}

//Constructor for every population after the first
Population::Population(vector<Chromosome> popVector)
{
	populationVector = popVector;

	for (int i = 0; i < populationVector.size(); i++)
		selectedIndex.push_back(false);

	sort(populationVector.begin(), populationVector.end());

	calculateAvgFitness(populationVector);
	l2Norm();
	selection();
	crossover();
	mutation();
}

//Calculate the average fitness for the population
void Population::calculateAvgFitness(vector<Chromosome> passedVector)
{
	double sum = 0;

	for (int i = 0; i < passedVector.size(); i++)
	{
		sum += passedVector[i].getFitness();
		if (passedVector[i].getFitness() > maxFitness)
		{
			maxFitness = passedVector[i].getFitness();
			maxFitnessChromosome = passedVector[i];
		}
	}

	averageFitness = (sum / passedVector.size());
}

//Create the L2 distribution
void Population::l2Norm()
{
	double sum = 0;

	for (int i = 0; i < populationVector.size(); i++)
	{
		sum += pow(populationVector[i].getFitness(), 2);
	}

	for (int i = 0; i < populationVector.size(); i++)
	{
		l2.push_back(pow(populationVector[i].getFitness(), 2));
		l2[i] /= sum;
	}

	double l2Total = accumulate(l2.begin(), l2.end(), 0.0);

	for (int i = 1; i < l2.size(); i++)
	{
		l2[i] = (l2[i] + l2[i - 1]);
	}
}

//Select the chromosomes to breed according to L2 distribution
void Population::selection()
{
	random_device rand;
	mt19937 gen(rand());
	uniform_real_distribution<double> distL2(0.0, 1.0);

	for(int i = 0; i < populationVector.size() / 2;)
	{
		double temp = distL2(gen);
		for (int j = 1; j < l2.size(); j++)
		{
			if (temp < l2[j])
			{
				if (selectedIndex[j] == false)
				{
					selectedIndex[j] = true;
					i++;
				}
				break;
			}
		}
	}

	for (int i = 0; i < selectedIndex.size(); i++)
	{
		if (selectedIndex[i])
		{
			selectedChromosomes.push_back(populationVector[i]);
		}
	}
}

//Crossover at a random point in the chromosome to create two children, pass both parents and both children to the new generation
void Population::crossover()
{
	random_device rand;
	mt19937 rng(rand());

	Chromosome child1(true), child2(true);

	vector<bool> alreadyChosen;
	for (int i = 0; i < 500; i++)
		alreadyChosen.push_back(false);
	
	while (finalPopulation.size() < 500)
	{
		uniform_int_distribution<mt19937::result_type> distCrossover(0, selectedChromosomes.size() - 1);
		int parent1Index = distCrossover(rng);
		int parent2Index = distCrossover(rng);

		while (alreadyChosen[parent1Index] == true)
		{
			int parent1Index = distCrossover(rng);
		}

		while (alreadyChosen[parent2Index] == true)
			int parent2Index = distCrossover(rng);

		Chromosome parent1 = selectedChromosomes[parent1Index];
		Chromosome parent2 = selectedChromosomes[parent2Index];

		while (parent1Index == parent2Index)
			parent2Index = distCrossover(rng);

		uniform_int_distribution<mt19937::result_type> distDivider(1, parent1.getSelectedItemsSize() - 2);
		int dividingLine = distDivider(rng);

		for (int i = 0; i < parent1.getSelectedItemsSize(); i++)
		{
			if (i < dividingLine)
			{
				child1.setSelectedItemsOfIndex(i, parent1.getSelectedItemsAtIndex(i));
				child2.setSelectedItemsOfIndex(i, parent2.getSelectedItemsAtIndex(i));
			}
			else
			{
				child2.setSelectedItemsOfIndex(i, parent1.getSelectedItemsAtIndex(i));
				child1.setSelectedItemsOfIndex(i, parent2.getSelectedItemsAtIndex(i));
			}
		}
		child1.calculateFitness();
		child2.calculateFitness();
		finalPopulation.push_back(child1);
		finalPopulation.push_back(child2);
		finalPopulation.push_back(parent1);
		finalPopulation.push_back(parent2);
	}

	for (int i = 0; i < selectedChromosomes.size(); i++)
		finalPopulation.push_back(selectedChromosomes[i]);

	sort(finalPopulation.begin(), finalPopulation.end());
}

//Mutate a gene given a 1/10000 chance
void Population::mutation()
{
	random_device rand;
	mt19937 rng(rand());
	uniform_int_distribution<mt19937::result_type> distMutate(0, 9999);

	for (int i = 0; i < finalPopulation.size(); i++)
	{
		for (int j = 0; j < finalPopulation[i].getSelectedItemsSize(); j++)
		{
			int temp = distMutate(rng);
			if (temp == 1)
			{
				if (finalPopulation[i].getSelectedItemsAtIndex(j))
				{
					finalPopulation[i].setSelectedItemsOfIndex(j, false);
				}
				else
					finalPopulation[i].setSelectedItemsOfIndex(j, true);
			}
		}
	}
}