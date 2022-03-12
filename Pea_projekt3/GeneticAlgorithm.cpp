#include "GeneticAlgorithm.h"
#include <random>

GeneticAlgorithm::GeneticAlgorithm(Solution solution) {
	matrix = solution.matrix;
	numberOfCities = solution.numberOfCities;
	populationSize = 0;
	minCost = INT32_MAX;
	kindOfmutation = 1;
	
}

GeneticAlgorithm::~GeneticAlgorithm() {
	matrix.clear();
	numberOfCities = 0;
	int generation = 0;
	int populationSize = 0;
	int numberOfParticipants = 0;
	minPath.clear();
}


void GeneticAlgorithm :: fitness() {
	int fitness;

	for (int i = 0; i < populationSize; i++) {
		fitness = findCost(population[i]);;
		double fit = (double)1/fitness;
		fitnessVector[i] = fit;
		if (fitness < minCost) {
			minCost = fitness;
			minPath = population[i];
		}
	}
}


void GeneticAlgorithm::generatePopuation(){
	vector<int> memberOfPopulation;

	for (int i = 0; i < numberOfCities; i++) {
		memberOfPopulation.push_back(i);
	}
	
	for (auto i = 0; i < populationSize; i++) {
		shuffle(memberOfPopulation.begin(), memberOfPopulation.end(), random_device());
		population[i] = memberOfPopulation;
	}
}


int GeneticAlgorithm::findCost(vector<int>& path) {
	int cost = 0;
	int iterator = 0;

	for (int i = 1; i < path.size(); i++) {
		cost += matrix[path[iterator]][path[i]];
		iterator++;
	}

	cost += matrix[path[iterator]][path[0]];

	return cost;
}


void GeneticAlgorithm::nextGeneration(vector<vector<int>> toReproduction, double mutationRate) {
	newPopulation.clear();
	while(newPopulation.size() < population.size() ){

		int indexOfParentA = rand() % toReproduction.size();
		int indexOfParentB;

		do {
			indexOfParentB = rand() % toReproduction.size();
		} while (indexOfParentA == indexOfParentB);

		crossover(toReproduction[indexOfParentA], toReproduction[indexOfParentB],mutationRate);

	}

	if (newPopulation.size() != population.size()) {
		newPopulation.pop_back();
	}

	population = newPopulation;
}


vector<vector<int>> GeneticAlgorithm::tournament(double crossoverRate) {
	int numberOfParticipants = population.size() / 10;
	vector<int> indexesOfParticipants;
	indexesOfParticipants.resize(numberOfParticipants);
	int indexOfWinner = 0;
	vector<vector<int>> toReproduction;
	double best, current;

	for (int i = 0; i < numberOfParticipants; i++) {
		indexesOfParticipants[i] = -1;
	}
	
	for (int j = 0; j < population.size()*crossoverRate; j++) {
		best = 0;
		for (int i = 0; i < numberOfParticipants; i++) {
			int participant = rand() % population.size();
			
			if (find(indexesOfParticipants.begin(), indexesOfParticipants.end(), participant) != indexesOfParticipants.end()) {
				i--;
			}
			else {
				indexesOfParticipants[i] = participant;
				current = fitnessVector[participant];
				if (current > best) {
					best = current;
					indexOfWinner = participant;
				}
			}
		}
		
		toReproduction.push_back(population[indexOfWinner]);
	}
	return toReproduction;

}


void GeneticAlgorithm::crossover(vector<int> parentA, vector<int> parentB, double mutationRate) {

	int start = (rand() % parentA.size());
	int stop = (rand() % parentA.size());

	if (start > stop) {
		int buffor = start;
		start = stop;
		stop = buffor;
	}


	vector<int> child1;
	child1.resize(numberOfCities);
	vector<int> child2;
	child2.resize(numberOfCities);

	for (int i = 0; i < numberOfCities; i++) {
		child1[i] = -1;
		child2[i] = -1;
	}

	for (int i = start; i < stop + 1; i++) {
		child1[i] = parentA[i];
		child2[i] = parentB[i];
	}

	int currentCityIndex = (stop) % numberOfCities;
	int currentCityInA = 0;
	int currentCityInB = 0;
	int itera1 = (stop + 1) % numberOfCities;
	int itera2 = (stop + 1) % numberOfCities;


	for (int i = 0; i < numberOfCities; i++) {
		currentCityIndex++;
		if (currentCityIndex >= numberOfCities) {
			currentCityIndex = 0;
		}
		
		currentCityInA = parentA[currentCityIndex];
		currentCityInB = parentB[currentCityIndex];
		
		
		if (!(find(child1.begin(), child1.end(), currentCityInB) != child1.end())) {
			child1[itera1] = currentCityInB;
			itera1++;
			if (itera1 >= numberOfCities) {
				itera1 = 0;
			}
			
		}
	
		
		if (!(find(child2.begin(), child2.end(), currentCityInA) != child2.end())) {
			child2[itera2] = currentCityInA;
			itera2++;
			if (itera2 >= numberOfCities) {
				itera2 = 0;
			}
			
		}


	}	

	if (kindOfmutation == 1) {
		mutate(child1, mutationRate);
		mutate(child2, mutationRate);
	}
	else {
		mutate2(child1, mutationRate);
		mutate2(child2, mutationRate);
	}

	newPopulation.push_back(child1);
	newPopulation.push_back(child2);
}


void GeneticAlgorithm::mutate(vector<int> &picked, double mutationRate) {
	
	if (((double)rand() / (RAND_MAX)) < mutationRate) {
		int current = rand() % picked.size();
		int next;

		do {
			next = rand() % picked.size();
		} while (current == next);

		iter_swap(picked.begin() + current, picked.begin() + next);
	}

}


void GeneticAlgorithm::mutate2(vector<int>& picked, double mutationRate) {
	
	if (((double)rand() / (RAND_MAX)) < mutationRate) {
		int current = rand() % picked.size();
		int next;

		do {
			next = rand() % picked.size();
		} while (current == next);

		if (current > next) {
			int buffor = current;
			current = next;
			next = buffor;
		}
		reverse(picked.begin() + current, picked.begin() + next);
	}
	

}


void GeneticAlgorithm::solveGeneticAlgorithm(int startPopulationSize, int stop, double mutationRate, double crossoverRate, int mutation) {
	kindOfmutation = mutation;
	MeasureTime time;
	populationSize = startPopulationSize;
	fitnessVector.resize(populationSize);
	population.resize(populationSize);
	time.start();
	generatePopuation();
	fitness();

	while (time.totalTime() < stop) {
		vector<vector<int>> toReproduction;
		toReproduction.resize(population.size() * crossoverRate);
		toReproduction = tournament(crossoverRate);
		nextGeneration(toReproduction,mutationRate);
		fitness();
		time.stop();
	}
	
}