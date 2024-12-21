#include "Generation.h"
#include <iomanip>

//Constructor to create the populations and output the data
Generation::Generation()
{
	ofstream fout;
	fout.open("GenerationLog.txt");

	while (generationalImprovement > 1.001)
	{
		fout << "Generation #" << generationNumber + 1 << endl;
		fout << "Average Fitness: " << currentGeneration.getAvgFitness() << endl;
		fout << "Max Fitness: " << currentGeneration.getMaxFitness() << endl << endl;

		fitnessVector.push_back(currentGeneration.getAvgFitness());
		createNewGeneration();

		if (currentGeneration.getMaxFitness() > overallMaxFitnessChromosome.getFitness())
			overallMaxFitnessChromosome = currentGeneration.getMaxFitnessChromosome();


		if (fitnessVector.size() > 10)
		{
			generationalImprovement = (fitnessVector[generationNumber] / fitnessVector[generationNumber - 10]);
		}

		generationNumber++;
	}

	fout << "Generation #" << generationNumber + 1 << endl;
	fout << "Average Fitness: " << currentGeneration.getAvgFitness() << endl;
	fout << "Max Fitness: " << currentGeneration.getMaxFitness() << endl << endl;

	if (currentGeneration.getMaxFitness() > overallMaxFitnessChromosome.getFitness())
		overallMaxFitnessChromosome = currentGeneration.getMaxFitnessChromosome();


	fout << endl << "Number of Generations: " << generationNumber + 1 << endl;
	fout << "Final Max Fitness: " << overallMaxFitnessChromosome.getFitness() << endl;

	fout << endl << "Max Fitness Chromosome: " << endl;
	fout << "Total Utility: " << overallMaxFitnessChromosome.getFitness() << endl;
	fout << "Items Taken: " << endl;
	for (int i = 0; i < overallMaxFitnessChromosome.getSelectedItemsSize(); i++)
	{
		if (overallMaxFitnessChromosome.getSelectedItemsAtIndex(i))
		{
			fout << left << setw(15) << "Item Number: " << setw(5) << i + 1;
			fout << setw(10) << "Utility: " << setw(5) << overallMaxFitnessChromosome.getItemListAtIndexUtility(i);
			fout << setw(15) << "Weight: " << setw(5) << overallMaxFitnessChromosome.getItemListAtIndexWeight(i) << endl;
		}
	}
}

//Create a new population/generation
void Generation::createNewGeneration()
{
	currentGeneration = Population(currentGeneration.getFinalPop());
}