/*
Suhail Attaelmanan
Apr 12, 2024
FileData.cpp: Implementation file for collecting file data.
*/

#include "FileData.h"
#include <filesystem>
#include <regex>

using namespace std;
namespace fs = filesystem;

/*
Name: FileData constructor
Purpose: Initializes a FileData object with the provided folder path and filter pattern.
Parameters:
	- const string& folder: The path to the folder to collect file information from.
	- const string& filterPattern: The regular expression filter pattern to limit file collection (optional).
Return: None
*/

FileData::FileData(const string& folder, const string& filterPattern)
	: folderPath(folder), filterPattern(filterPattern) {}

/*
Name: collectFileInfo
Purpose: Collects file information for the specified folder.
Parameters: None
Return: None
*/

void FileData::collectFileInfo() {
	countFiles(folderPath);
}

/*
Name: getFileInfos
Purpose: Retrieves the vector of FileInfo objects collected by the FileData object.
Parameters: None
Return: const vector<FileInfo>& - Reference to the vector of FileInfo objects.
*/

const vector<FileInfo>& FileData::getFileInfos() const {
	return fileInfos;
}

/*
Name: countFiles
Purpose: Recursively counts files and collects their information in the provided folder.
Parameters:
	- const string& folder: The path to the folder to count files in.
Return: None
*/
void FileData::countFiles(const string& folder) {
	for (const auto& entry : fs::directory_iterator(folder)) {
		if (fs::is_regular_file(entry)) {
			// Extract the extension of the current file
			string ext = entry.path().extension().string();
			// Remove the leading dot from the extension, if present
			if (!ext.empty() && ext[0] == '.') {
				ext = ext.substr(1);
			}
			// If a filter pattern is provided, check if the file extension matches it
			if (!filterPattern.empty()) {
				// Create a regular expression from the filter pattern
				regex pattern(filterPattern);
				// If the file extension doesn't match the filter pattern, skip processing it
				if (!regex_match(ext, pattern)) {
					continue;
				}
			}
			// Check if the file extension already exists in the FileInfo vector
			auto it = find_if(fileInfos.begin(), fileInfos.end(),
				[&ext](const FileInfo& fileInfo) {
					return fileInfo.extension == ext;
				});
			// If the file extension is found, update its count and size
			if (it != fileInfos.end()) {
				it->count++;
				it->size += fs::file_size(entry);
			}
			// If the file extension is not found, add a new entry to the FileInfo vector
			else {
				FileInfo fileInfo = { ext, 1, fs::file_size(entry) };
				fileInfos.push_back(fileInfo);
			}
		}
		// If the current entry is a directory, recursively process it
		else if (fs::is_directory(entry)) {
			countFiles(entry.path().string());
		}
	}
}