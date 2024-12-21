#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

class Chromosome
{
public:
	Chromosome();
	Chromosome(bool isChild);
	double getTotalWeight() { return totalWeight; }
	double getTotalUtility() { return totalUtility; }
	double getFitness() { return fitness; }
	void setSelectedItemsOfIndex(int index, bool value) { selectedItems[index] = value; }
	bool getSelectedItemsAtIndex(int index) { return selectedItems[index]; }
	int getSelectedItemsSize() { return selectedItems.size(); }
	double getItemListAtIndexUtility(int index) { return itemList[index].first; }
	double getItemListAtIndexWeight(int index) { return itemList[index].second; }
	void calculateFitness();

	bool operator< (const Chromosome& c2) const { return fitness < c2.fitness; }

private:
	//Vector of bools to compare against itemList. If true, the item at that index in both vectors has been chosen
	vector<bool> selectedItems;
	//Vector of pairs from the input file
	vector<pair<double, double>> itemList;
	double totalWeight = 0, totalUtility = 0, fitness = 0;
	int chromosomeSize = 0;
};

