#include "FileProcessing.h"

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std::string_literals;

bool convertToTxt(const std::string & filepath, const std::string & flags, const std::string & destinationPath)
{
	struct stat info;
	if (stat(filepath.c_str(), &info))
	{
		std::cout << "Can't open file " << filepath << "\n\n";
		return false;
	}

	unsigned int i = destinationPath.length();
	for (; destinationPath[i] != '/'; i--);

	std::string path = destinationPath.substr(0, i);
	std::string filename = destinationPath.substr(i+1);

	if (stat(path.c_str(), &info))
		CreateDirectory(path.c_str(), NULL);

	std::fstream database("./Files/database.txt", std::fstream::in | std::fstream::out |
			std::fstream::app);

	std::string line;
	std::string temp;
	while (std::getline(database, line))
	{
		temp += line;
	}
	database.clear();

	if (temp.find(filename) == std::string::npos)
		database << filename << "\n";

	database.close();

	std::string command = "Vendor\\pdftotext "s +  flags + " "s + filepath + " "s + destinationPath;
	system(command.c_str());

	processText(destinationPath);

	struct stat buffer;
	return (!stat(destinationPath.c_str(), &buffer));

}

void processText(const std::string& filepath)
{
	std::string processedFile = filepath + "to_process"s;

	rename(filepath.c_str(), processedFile.c_str());

	std::ifstream oldFile(processedFile);
	std::ofstream newFile(filepath);

	std::string paragraph;
	std::string line;

	while (std::getline(oldFile, line))
	{
		int tempLength = line.length();

		if (tempLength > 50 || (tempLength > 0 && line[tempLength-1] == '.'))
		{
			newFile << line << "\n";
		}
	}

	oldFile.close();
	newFile.close();

	remove(processedFile.c_str());
}
