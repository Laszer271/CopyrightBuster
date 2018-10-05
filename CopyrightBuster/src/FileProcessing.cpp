#include "FileProcessing.h"

#include <string>
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

	struct stat buffer;
	return (stat(destinationPath.c_str(), &buffer) == 0);

}
