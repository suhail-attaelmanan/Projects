/*
Suhail Attaelmanan
Apr 12, 2024
Options.h: Header file for parsing command-line options.
*/

#pragma once

#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <vector>

class Options {
public:
	Options(int argc, char* argv[]);

	std::string getFolderPath() const;

private:
	std::vector<std::string> args;
	std::string folderPath;
};

#endif