/*
Suhail Attaelmanan
Apr 12, 2024
Options.cpp: Implementation file for parsing command-line options.
*/

#include "Options.h"
#include <filesystem>

using namespace std;

Options::Options(int argc, char* argv[]) {
	if (argc > 1) {
		// Parse command-line arguments and store them in the args vector
		for (int i = 1; i < argc; ++i) {
			args.push_back(argv[i]);
		}

		// Extract folder path if provided
		if (args[0][0] != '-') {
			folderPath = args[0];
			args.erase(args.begin());
		}
	}
	else {
		// If no arguments are provided, set folderPath to the current directory
		folderPath = filesystem::current_path().string();
	}
}

string Options::getFolderPath() const {
	return folderPath;
}