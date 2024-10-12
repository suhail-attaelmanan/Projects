/*
Suhail Attaelmanan
Apr 12, 2024
Mainfileusage.cpp: This file will contain the main() function.
*/

#include <iostream>
#include "Options.h"
#include "FileData.h"
#include "PrintReport.h"

using namespace std;

int main(int argc, char* argv[]) {

	// Display the program title
	cout << "fileusage (c) 2024-4, Suhail Attaelmanan" << endl;

	// if too many args
	if (argc > 4) {
		cerr << "Error: Error: too many commandline arguments";
		return 1;
	}

	// Check if the help switch is provided
	if (argc > 1 && (string(argv[1]) == "-h" || string(argv[1]) == "--help")) {
		PrintReport::displayHelpMessage();
		return 1;
	}

	// Initialize variables for command-line arguments
	bool reverseOrder = false;
	bool sortBySize = false;
	string folderPath;
	string filterPattern;

	// Parse command-line arguments
	if (argc == 1) {
		// Use the current directory if no arguments are provided
		folderPath = ".";
	}
	else if (argc > 3 && (string(argv[1]) == "-x")) {
		// If the filter switch (-x) is provided, set the filter pattern and folder path accordingly
		filterPattern = argv[2];
		folderPath = argv[3];
	}
	else if (argc > 2 && (string(argv[1]) == "-sr" || string(argv[1]) == "-rs" || string(argv[1]) == "-s" || string(argv[1]) == "-r")) {
		// Handle sorting options (-s, -r, -sr) and set the folder path accordingly
		if (argc > 3 && string(argv[1]) == "-sr") {
			reverseOrder = true;
			sortBySize = true;
			folderPath = argv[3];
		}
		else {
			folderPath = argv[2];
			if (argc > 2 && string(argv[1]) == "-r") {
				reverseOrder = true;
			}
			if (argc > 2 && string(argv[1]) == "-s") {
				sortBySize = true;
			}
		}
	}
	else {
		// If no switch is provided, consider the first argument as the folder path
		folderPath = argv[1];
	}

	// Initialize Options object to handle command-line arguments
	Options options(argc, argv);

	// Create FileData object with the specified folder path and filter pattern
	FileData fileData(folderPath, filterPattern);

	// Collect file information based on the specified filter pattern
	fileData.collectFileInfo();

	// Check if there are any files or folders to analyze
	if (fileData.getFileInfos().empty()) {
		cout << "No files or folders here." << endl;
	}
	else {
		// Print the file information based on sorting and ordering options
		if (sortBySize) {
			if (reverseOrder) {
				PrintReport::printSortedBySizeDescending(fileData.getFileInfos(), folderPath);
			}
			else {
				PrintReport::printSortedBySize(fileData.getFileInfos(), folderPath);
			}
		}
		else {
			PrintReport::print(fileData.getFileInfos(), folderPath, reverseOrder);
		}
	}
}