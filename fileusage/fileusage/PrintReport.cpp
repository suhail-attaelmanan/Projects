/*
Suhail Attaelmanan
Apr 12, 2024
PrintReport.cpp: Implementation file for printing the report.
*/

#include "PrintReport.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

/*
Name: displayHelpMessage
Purpose: Display the help message for using the program.
Parameters: None
Return: None
*/

void PrintReport::displayHelpMessage() {
	cout << "Usage: fileusage[-hrRsSvc+#jw(x regularexpression)] [folder]\n";
}

/*
Name: compareFileInfo
Purpose: Comparison function to sort FileInfo structs by count in descending order.
Parameters:
	- const FileInfo& a: The first FileInfo object to compare.
	- const FileInfo& b: The second FileInfo object to compare.
Return: bool - True if the count of FileInfo a is greater than FileInfo b, false otherwise.
*/

bool PrintReport::compareFileInfo(const FileInfo& a, const FileInfo& b) {
	return a.count > b.count;
}

/*
Name: compareFileSize
Purpose: Comparison function to sort FileInfo structs by size in ascending order.
Parameters:
	- const FileInfo& a: The first FileInfo object to compare.
	- const FileInfo& b: The second FileInfo object to compare.
Return: bool - True if the size of FileInfo a is less than FileInfo b, false otherwise.
*/

bool PrintReport::compareFileSize(const FileInfo& a, const FileInfo& b) {
	return a.size < b.size; // Compare file sizes in ascending order
}

/*
Name: print
Purpose: Print the file report.
Parameters:
	- const vector<FileInfo>& fileInfos: Vector containing file information.
	- const string& directory: Directory path.
	- bool reverseOrder: Flag indicating whether to reverse the order of printing (optional).
Return: None
*/

void PrintReport::print(const vector<FileInfo>& fileInfos, const string& directory, bool reverseOrder) {
	// Sorting by extension alphabetically
	vector<FileInfo> sortedFileInfos = fileInfos;
	sort(sortedFileInfos.begin(), sortedFileInfos.end(), [](const FileInfo& a, const FileInfo& b) {
		return a.extension < b.extension;
		});

	// Reverse the order if specified
	if (reverseOrder) {
		reverse(sortedFileInfos.begin(), sortedFileInfos.end());
	}

	// Initialize sum variables
	int extCountSum = 0;
	int totalCountSum = 0;
	long long totalSizeSum = 0;

	cout << "All files: " << directory << "\n\n";
	cout << setw(20) << "Ext" << setw(20) << "#" << setw(22) << "Total\n\n";
	for (const auto& fileInfo : sortedFileInfos) {
		string extension = "." + fileInfo.extension;
		cout << setw(20) << extension
			<< setw(20) << fileInfo.count
			<< setw(20) << formatSize(fileInfo.size) << endl;

		// Update sum variables
		extCountSum++;
		totalCountSum += fileInfo.count;
		totalSizeSum += fileInfo.size;
	}

	// Output sum row
	cout << "\n" << setw(10) << ""
		<< setw(10) << extCountSum
		<< setw(20) << totalCountSum
		<< setw(20) << formatSize(totalSizeSum);
}

/*
Name: print
Purpose: Print the file report without considering order.
Parameters:
	- const vector<FileInfo>& fileInfos: Vector containing file information.
	- const string& directory: Directory path.
Return: None
*/

void PrintReport::print(const vector<FileInfo>& fileInfos, const string& directory) {
	print(fileInfos, directory, false); // Call the main print function with reverseOrder set to false
}

/*
Name: printSortedBySize
Purpose: Print the file report sorted by file size in ascending order.
Parameters:
	- const vector<FileInfo>& fileInfos: Vector containing file information.
	- const string& directory: Directory path.
Return: None
*/

void PrintReport::printSortedBySize(const vector<FileInfo>& fileInfos, const string& directory) {
	// Sorting by file size in ascending order
	vector<FileInfo> sortedFileInfos = fileInfos;
	sort(sortedFileInfos.begin(), sortedFileInfos.end(), compareFileSize);

	print(sortedFileInfos, directory); // Call the main print function with sortedFileInfos
}

/*
Name: printSortedBySizeDescending
Purpose: Print the file report sorted by file size in descending order.
Parameters:
	- const vector<FileInfo>& fileInfos: Vector containing file information.
	- const string& directory: Directory path.
Return: None
*/

void PrintReport::printSortedBySizeDescending(const vector<FileInfo>& fileInfos, const string& directory) {
	// Sorting by file size in descending order
	vector<FileInfo> sortedFileInfos = fileInfos;
	sort(sortedFileInfos.begin(), sortedFileInfos.end(), [](const FileInfo& a, const FileInfo& b) {
		return a.size > b.size;
		});

	print(sortedFileInfos, directory); // Call the main print function with sortedFileInfos
}

/*
Name: formatSize
Purpose: Format the file size with commas as separators.
Parameters:
	- long long size: The size of the file.
Return: string - Formatted size string.
*/

string PrintReport::formatSize(long long size) {
	string sizeStr = to_string(size);
	int len = sizeStr.length();
	for (int i = len - 3; i > 0; i -= 3) {
		sizeStr.insert(i, ",");
	}
	return sizeStr;
}