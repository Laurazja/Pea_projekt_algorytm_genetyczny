#pragma once
#include "Solution.h"

using namespace std;

class GeneticAlgorithm
{
public:
	int populationSize;
	vector<vector<int>> matrix;
	int numberOfCities;
	vector<vector<int>> population;
	vector<vector<int>> newPopulation;
	vector<double> fitnessVector;
	vector<int> minPath;
	int minCost;
	int kindOfmutation;

	GeneticAlgorithm(Solution solution);
	~GeneticAlgorithm();

	void generatePopuation();
	void mutate(vector<int> &picked, double mutationRate);
	void mutate2(vector<int>& picked, double mutationRate);
	void solveGeneticAlgorithm(int startPopulationSize, int stop, double mutationRate, double crossoverRate, int mutation);
	vector<vector<int>> tournament(double crossoverRate);
	void fitness();
	int findCost(vector<int>& path);
	void nextGeneration(vector<vector<int>> toReproduction, double mutationRate);
	void crossover(vector<int> parentA, vector<int> parentB, double mutationRate);

};

