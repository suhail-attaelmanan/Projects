/*
stats_main.cpp
Suhail Attaelmanan
July 12 2024
main function for stats
*/

#include "stats_functions_header.hpp"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {

	// Title 
	cout << "stats (2024), (c) 2024 Suhail Attaelmanan" << endl;

	// Data set in a vector
	vector<double> data;

	if (argc == 2) {
		ifstream file(argv[1]);
		if (file.is_open()) {
			double number;
			while (file >> number) {
				data.push_back(number);
			}
			file.close();
		}
		else { // file opening error
			cerr << "Error <" << argv[1] << "> failed open.\n";
			return EXIT_FAILURE;
		}
	}
	else {
		// No file in args
		cout << "Enter a list of whitespace-separated real numbers terminated by ^Z or 'end'.\n";
		readData(data);
	}

	// If data is empty file or cin
	if (data.empty()) {
		cerr << "empty data set!\nquitting...";
		return EXIT_FAILURE;
	}

	printStats(data);

	return EXIT_SUCCESS; //exit the program with success
}
