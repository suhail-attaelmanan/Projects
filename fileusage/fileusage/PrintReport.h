/*
Suhail Attaelmanan
Apr 12, 2024
PrintReport.h: Header file for printing the report.
*/

#pragma once

#ifndef PRINTREPORT_H
#define PRINTREPORT_H

#include <vector>
#include <string>
#include "FileData.h"

class PrintReport {
public:
	// Print the file report without considering order
	static void print(const std::vector<FileInfo>& fileInfos, const std::string& directory);

	// Print the file report with optional reverse order
	static void print(const std::vector<FileInfo>& fileInfos, const std::string& directory, bool reverseOrder);

	// Print the file report sorted by file size in ascending order
	static void printSortedBySize(const std::vector<FileInfo>& fileInfos, const std::string& directory);

	// Print the file report sorted by file size in descending order
	static void printSortedBySizeDescending(const std::vector<FileInfo>& fileInfos, const std::string& directory);

	// Display the help message
	static void displayHelpMessage();

	// Format the file size with commas as separators
	static std::string formatSize(long long size);

	// Comparison function to sort FileInfo structs by count in descending order
	static bool compareFileInfo(const FileInfo& a, const FileInfo& b);

	// Comparison function to sort FileInfo structs by size in ascending order
	static bool compareFileSize(const FileInfo& a, const FileInfo& b);
};

#endif // PRINTREPORT_H
