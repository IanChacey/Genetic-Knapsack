#include "Chromosome.h"

//Constructor for initial chromosome
Chromosome::Chromosome()
{
	ifstream fin;
	fin.open("Program2Input.txt");

	while (!fin.eof())
	{
		pair<double, double> itemPair;
		fin >> itemPair.first >> itemPair.second;
		itemList.push_back(itemPair);
	}

	random_device rand;
	mt19937 rng(rand());
	uniform_int_distribution<mt19937::result_type> distItemList(0, itemList.size() - 1);

	for (int i = 0; i < itemList.size(); i++)
		selectedItems.push_back(false);

	for (int i = 0; i < itemList.size() / 20; i++)
	{
		int temp = distItemList(rng);

		selectedItems.at(temp) = true;
	}

	calculateFitness();
}

//Constructor to create a blank child chromosome
Chromosome::Chromosome(bool isChild)
{
	ifstream fin;
	fin.open("Program2Input.txt");

	while (!fin.eof())
	{
		pair<double, double> itemPair;
		fin >> itemPair.first >> itemPair.second;
		itemList.push_back(itemPair);
	}
	if (isChild)
	{
		for (int i = 0; i < itemList.size(); i++)
			selectedItems.push_back(false);
	}
}

//Calculate the fitness of the chromosome
void Chromosome::calculateFitness()
{
	totalUtility = 0;
	totalWeight = 0;
	for (int i = 0; i < selectedItems.size(); i++)
	{
		if (selectedItems[i])
		{
			totalUtility += itemList[i].first;
			totalWeight += itemList[i].second;
		}
	}

	if (totalWeight > 500)
		fitness = 1;
	else
		fitness = totalUtility;
}