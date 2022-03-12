#include "Menu.h"

void Menu::mainMenu() {
	char option = 0;
	string fileName = "";
	double stopTime = 60;
	double mutationRate = 0.01;
	double crossoverRate = 0.8;
	int population = 20;
	int mutation = 1;

	while (option != 'e') {

		cout << "Wybierz opcje: " << endl
			<< "1. Wczytaj dane z pliku" << endl
			<< "2. Wprowadz kryterium stopu" << endl
			<< "3. Ustaw wielkosc populacji poczatkowej" << endl
			<< "4. Ustaw wspolczynnik mutacji" << endl
			<< "5. Ustaw wspolczynnik krzyzowania" << endl
			<< "6. Wybor metody" << endl
			<< "7. Uruchom alogorytm" << endl
			<< "e. Wyjdz" << endl;
		cin >> option;

		switch (option) {
		case '1':
			cout << "Podaj nazwe pliku: ";
			cin >> fileName;
			lastSolution.readFromFile(fileName);
			break;
		case '2':
			cout << endl << "Podaj czas w sekundach: ";
			cin >> stopTime;
			//stopTime = stopTime * 1000000;
			break;
		case '3':
			cout << endl << "Podaj wilekosc populacji: ";
			cin >> population;
			break;
		case '4':
			cout << endl << "Podaj wartosc wspolczynnika mutacji: ";
			cin >> mutationRate;
			break;
		case '5':
			cout << endl << "Podaj wartosc wspolczynnika krzyzowania: ";
			cin >> crossoverRate;
			break;
		case '6':
			cout << endl << "Wybierz stosob mutacji: \n1.Zamiana dwoch losowych elementow\n2.Mutacja przez inwersje\n";
			cin >> mutation;
			if ((mutation > 2) && (mutation < 1)) {
				mutation = 1;
				cout << "Podano nie poprawna opcje mutacji. Sposob mutacji ustawiono na domyslna wartosc.\n";
			}
			break;
		case '7':
			if (!lastSolution.matrix.empty()) {
				GeneticAlgorithm gen(lastSolution);
				gen.solveGeneticAlgorithm(population, stopTime, mutationRate, crossoverRate, mutation);
				lastSolution.minCost = gen.minCost;
				lastSolution.minPath = gen.minPath;
				lastSolution.displaySolution();
			}
			else {
				cout << "Brak danych do wykonania algorytmu" << endl;
			}
			break;
		case 'e':
			cout << "Zakonczenie programu" << endl;
			break;
		default:
			cout << "Zle oznaczenie opcji" << endl;
			break;
		}
	}
}


void Menu::testMenu() {
	int time = 120;
	string fileName = "";
	cout << "Podaj nazwe pliku: ";
	cin >> fileName;
	lastSolution.readFromFile(fileName);

	cout << "pop 400\n";
	for (int i = 0; i < 5; i++) {
		GeneticAlgorithm gen(lastSolution);
		gen.solveGeneticAlgorithm(400, time, 0.01, 0.8, 1);
		lastSolution.minCost = gen.minCost;
		lastSolution.minPath = gen.minPath;
		lastSolution.displaySolution();

	}

	cout << "pop 800\n";
	for (int i = 0; i < 5; i++) {
		GeneticAlgorithm gen(lastSolution);
		gen.solveGeneticAlgorithm(1000, time, 0.01, 0.8, 1);
		lastSolution.minCost = gen.minCost;
		lastSolution.minPath = gen.minPath;
		lastSolution.displaySolution();

	}

	cout << "pop 1000";
	for (int i = 0; i < 5; i++) {
		GeneticAlgorithm gen(lastSolution);
		gen.solveGeneticAlgorithm(2000, time, 0.01, 0.8, 1);
		lastSolution.minCost = gen.minCost;
		lastSolution.minPath = gen.minPath;
		lastSolution.displaySolution();

	}


	cout << "pop 400\n";
	for (int i = 0; i < 5; i++) {
		GeneticAlgorithm gen(lastSolution);
		gen.solveGeneticAlgorithm(400, time, 0.01, 0.8, 2);
		lastSolution.minCost = gen.minCost;
		lastSolution.minPath = gen.minPath;
		lastSolution.displaySolution();

	}

	cout << "pop 800\n";
	for (int i = 0; i < 5; i++) {
		GeneticAlgorithm gen(lastSolution);
		gen.solveGeneticAlgorithm(800, time, 0.01, 0.8, 2);
		lastSolution.minCost = gen.minCost;
		lastSolution.minPath = gen.minPath;
		lastSolution.displaySolution();

	}

	cout << "pop 1000";
	for (int i = 0; i < 5; i++) {
		GeneticAlgorithm gen(lastSolution);
		gen.solveGeneticAlgorithm(1000, time, 0.01, 0.8, 2);
		lastSolution.minCost = gen.minCost;
		lastSolution.minPath = gen.minPath;
		lastSolution.displaySolution();

	}
	
}
