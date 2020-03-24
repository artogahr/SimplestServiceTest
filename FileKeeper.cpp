#include "FileKeeper.h"

FileKeeper::FileKeeper()
{
	fileCount = 0;
}
FileKeeper::FileKeeper(std::string filePath)
{
	this->inputFilePath = filePath;
	inputFile.open(inputFilePath);
	for (int i = 0; inputFile >> path; i++)
	{
		lockFile(path);
	}
	girdiDosyasiStream << inputFile.rdbuf();
	girdiDosyasiIcerigi = girdiDosyasiStream.str();
	girdiDosyasiSHA256 = sha256(girdiDosyasiIcerigi);
}
void FileKeeper::guncelle()
{
	inputFile.clear();
	inputFile.seekg(0);
	girdiDosyasiStream << inputFile.rdbuf();
	girdiDosyasiIcerigi = girdiDosyasiStream.str();
	yeniGirdiDosyasiSHA256 = sha256(girdiDosyasiIcerigi);
	if (yeniGirdiDosyasiSHA256 != girdiDosyasiSHA256)
	{
		filePaths.clear();
		for (int i = 0; i < fileHandles.size(); i++)
		{
			fileHandles[i]->close();
		}
		fileHandles.clear();
		for (int i = 0; inputFile >> path; i++)
		{
			filePaths.push_back(path);
			fileHandles.push_back(std::make_shared<std::ifstream>());
			fileHandles[i]->open(path);
		}
	}
}
bool FileKeeper::varmi(std::string filePath)
{
	if (std::find(filePaths.begin(), filePaths.end(), filePath) != filePaths.end())
	{
		return 1;
	}
	return 0;
}
void FileKeeper::lockFile(std::string path)
{
	filePaths.push_back(path);
	fileHandles.push_back(std::make_shared<std::ifstream>());
	fileHandles.back()->open(path);
}
void FileKeeper::unlockFile(std::string filePath)
{
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
	}
}
FileKeeper::~FileKeeper()
{
	for (int i = 0; i < fileHandles.size(); i++)
	{
		fileHandles[i]->close();
	}
	fileHandles.clear();
	filePaths.clear();
}