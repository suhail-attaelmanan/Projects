/*
Suhail Attaelmanan
Apr 12, 2024
FileData.h: Header file for collecting file data.
*/
#pragma once

#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>
#include <vector>

struct FileInfo {
	std::string extension;
	int count;
	long long size;
};

class FileData {
public:
	FileData(const std::string& folder, const std::string& filterPattern = "");

	void collectFileInfo();

	const std::vector<FileInfo>& getFileInfos() const;

private:
	std::string folderPath;
	std::string filterPattern; // Member variable to store the filter pattern

	// Vector to store file information
	std::vector<FileInfo> fileInfos;

	// Helper function to count files in a directory
	void countFiles(const std::string& folder);
};

#endif // FILEDATA_H