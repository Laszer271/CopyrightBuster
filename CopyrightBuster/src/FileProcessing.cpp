#include "FileProcessing.h"

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std::string_literals;

bool convertToTxt(const std::string & filepath, const std::string & flags, const std::string & destinationPath)
{
	unsigned int i = destinationPath.length();
	for (; destinationPath[i] != '/'; i--);

	std::string path = destinationPath.substr(0, i);

	struct stat info;
	if (stat(path.c_str(), &info) != 0)
		CreateDirectory(path.c_str(), NULL);

	std::string command = "pdftotext "s +  flags + " "s + filepath + " "s + destinationPath;
	system(command.c_str());

	processText(destinationPath);

	struct stat buffer;
	return (stat(destinationPath.c_str(), &buffer) == 0);

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

		if (tempLength > 0 && tempLength < 150 && line[tempLength - 1] != '.')
			paragraph.clear();
		else if (tempLength > 0)
		{
			newFile << paragraph << line << "\n";
			paragraph.clear();
		}
	}

	oldFile.close();
	newFile.close();

	//remove(processedFile.c_str());
}
