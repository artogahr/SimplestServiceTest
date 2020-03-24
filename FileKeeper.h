#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "SHA256.h"

class FileKeeper {
private:
	int fileCount;
	std::ifstream inputFile;
	std::vector<std::string> filePaths;
	std::string inputFilePath, path, girdiDosyasiIcerigi, girdiDosyasiSHA256, yeniGirdiDosyasiSHA256;
	std::vector<std::shared_ptr<std::ifstream>> fileHandles;
	std::ostringstream girdiDosyasiStream;
public:
	FileKeeper();
	FileKeeper(std::string filePath);
	void guncelle();
	bool varmi(std::string filePath);
	void lockFile(std::string filePath);
	void unlockFile(std::string filePath);
	~FileKeeper();
};
/*
	int index;
	auto it = std::find(filePaths.begin(), filePaths.end(), filePath);
	if (it == filePaths.end())
	{
		// name not in vector
	}
	else
	{
		index = std::distance(filePaths.begin(), it);
		fileHandles[index]->close();
		fileHandles.erase(fileHandles.begin() + index);
		filePaths.erase(it);
	}*/
