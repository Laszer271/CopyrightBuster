#include "Interface.h"
#include "FileProcessing.h"
#include "Raport.h"

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std::string_literals;

void menu()
{
	std::string command;

	std::cout << "Type help to see available commands\n\n";

	while (std::getline(std::cin, command))
	{
		std::string arguments[3];
		std::string commandname = command.substr(0, command.find(" "));
		command.erase(0, commandname.length() + 1);
		for (int i = 0; command.length() > 0 && i < 3; i++)
		{
			arguments[i] = command.substr(0, command.find(" "));
			command.erase(0, arguments[i].length() + 1);
		}

		if (command.length() > 0)
		{
			std::cout << "Invalid command\n\n";
			continue;
		}

		if (commandname == "help")
			help();
		else if (commandname == "filelist")
			filelist();
		else if (commandname == "remove")
			removeFile(arguments[0]);
		else if (commandname == "import")
			import(arguments[0]);
		else if (commandname == "rename")
			changeFilename(arguments[0], arguments[1]);
		else if (commandname == "delete")
			removeFile(arguments[0]);
		else if (commandname == "compare")
			compare(arguments[0], arguments[1], arguments[2][0]);
		else if (commandname == "quit" || commandname == "exit" || commandname == "q")
			return;
		else
			std::cout << "Invalid command";

		std::cout << "\n\n";
	}
}

void help()
{
	std::cout << "Commands:\n\n"
		"help [command] - shows help for specified command\n\n" <<
		"filelist - shows what files are in database\n\n" <<
		"delete [filename] - deletes specified file from database\n\n" <<
		"import [filepath] - imports specified file to database\n\n" <<
		"rename [file] [name] - renames file to name\n\n" <<
		"compare [file1] [file2] - compares file1 with file2 and prints results to the console\n\n" <<
		"compare [file1] all - compares file1 with all files from database and prints results to the console\n\n" <<
		"compare [filepath] [file] - compares file from filepath with file and prints results to the console\n\n" <<
		"compare [filepath] all - compares file from filepath with all files from database\nand prints results to the console\n\n" <<
		"compare [filepath1] [filepath2] - compares file from filepath1 with file from filepath2\nand prints results to the console\n\n" <<
		"save [specified compare...] - compares files from given compare's parameters\nand gives a txt file with the results of comparison to the user\n\n" <<
		"set_accuracy [acc] - sets accuracy as acc\n\n" <<
		"save_as [filepath] [specified compare...] - compares files from given compare's parameters\nand and creates a txt file at the specified path with the results of comparison to the user\n\n" <<
		"exit - exits the program\n\n" <<
		"quit - exits the program\n\n" <<
		"q - exits the program\n\n" << std::endl;
}

void help(const std::string command)
{

}

void filelist()
{
	std::ifstream file("./Files/database.txt");
	std::string line;

	int i = 0;
	while (std::getline(file, line))
	{
		i++;
		std::cout << i << ". " << line << '\n';
	}
	if (!i)
		std::cout << "Database is empty!\n\n";
}

bool removeFile(const std::string filename)
{
	if (filename == "database.txt"s)
	{
		std::cout << "You can't detele database!\n\n";
		return false;
	}
	if (removeFromDatabase(filename))
	{
		remove(("./Files/"s + filename).c_str());
		return true;
	}

	std::cout << "There is no file " << filename << " in the database!\n\n";
	return false;
}

bool import(const std::string filepath)
{
	int i = filepath.length();
	for (; filepath[i] != '.' && i > 0; i--);
	std::string extension = filepath.substr(i + 1);

	i = filepath.length();
	for (; filepath[i] != '/' && i > 0; i--);
	std::string filename = filepath.substr(i + 1);

	if (extension == "pdf"s)
		return convertToTxt(filepath, ""s, "./Files/"s + filename);
	else if (extension == "txt"s)
	{
		std::string destinationPath = "./Files/"s + filename;
		std::ifstream fileToProcess(filepath);
		std::ofstream processedFile(destinationPath);

		processedFile << fileToProcess.rdbuf();
		fileToProcess.close();
		processedFile.close();

		struct stat buffer;
		if (!stat(destinationPath.c_str(), &buffer))
		{
			processText(destinationPath);
			return true;
		}
	}
	else
	{
		std::cout << "Program can't handle the file extension: " << extension << '\n';
		return false;
	}	

	return false;
}

bool changeFilename(const std::string filename, const std::string name)
{
	std::ifstream file("./Files/database.txt");
	std::string line;

	if (name == "database.txt")
	{
		std::cout << "You cannot name your file database.txt!\n\n";
		file.close();
		return false;
	}

	bool itsf = false;
	while (std::getline(file, line))
	{
		if (name == line)
		{
			std::cout << "There is already file with this name in database!\n\n";
			file.close();
			return false;
		}
		if (line == filename)
			itsf = true;
	}
	if (!itsf)
	{
		std::cout << "There is no file such as " << filename << " in database!\n\n";
		file.close();
		return false;
	}
	
	removeFromDatabase(filename);
	std::ofstream database("./Files/database.txt", std::fstream::out | std::fstream::app);
	database << name << '\n';

	database.close();
	return true;
}

bool changeFilename(unsigned int which, const std::string name)
{
	std::ifstream file("./Files/database.txt");
	std::string line;

	int i;
	for (i = 1; std::getline(file, line) && i != which; i++);
	if (i != which)
	{
		std::cout << "There is less than " << which << " files in the database!\n\n";
		file.close();
		return false;
	}

	file.close();
	return changeFilename(line, name);
}

bool removeFromDatabase(const std::string& filename) 
{
	struct stat buffer;
	if (!stat("./Files/database.txt", &buffer))
		return false;

	rename("./Files/database.txt", "./Files/databaseTemp");
	std::ifstream baseToDelete("./Files/databaseTemp");
	std::ofstream baseToCreate("./Files/database.txt");
	std::string line; 

	while (std::getline(baseToDelete, line))
	{
		if (line != filename)
			baseToCreate << line << '\n';
	}

	baseToCreate.close();
	baseToDelete.close();
	remove("./Files/databaseTemp");
	return true;
}

bool compare(const std::string& arg1, const std::string& arg2, unsigned int accuracy)
{
	std::string filename1, filename2;
	int i = filename1.length();
	for (; arg1[i] != '/' && i > -1; i--);
	filename1 = arg1.substr(i + 1);

	for (int i = 0; i < arg1.length(); i++)
	{
		if (arg1[i] == '/')
		{
			if (!import(arg1))
			{
				std::cout << "Can't find " << arg1 << "\n\n";
				return false;
			}

			Raport rap("./Files/"s + filename1);
			if (arg2 == "all")
				rap.compareToAll(accuracy);
			else
				rap.compare("./Files/"s + arg2 , accuracy);

			removeFile(filename1);
			return true;
		}
	}

	Raport rap("./Files/"s + arg1);
	if (arg2 == "all")
		rap.compareToAll(accuracy);
	else
		rap.compare("./Files/"s + arg2, accuracy);
	return true;
}

// help - shows available commands
// help [command] - shows help for specified command
// filelist - shows what files are in database
// delete [filename] - deletes specified file from database
// import [filepath] - imports specified file to database
// rename [file] [name] - renames file to name
// compare [file1] [file2] - compares file1 with file2 and prints results to the console
// compare [file1] all - compares file1 with all files from database and prints results to the console
// compare [filepath] [file] - compares file from filepath with file and prints results to the console
// compare [filepath] all - compares file from filepath with all files from database and prints results to the console
// compare [filepath1] [filepath2] - compares file from filepath1 with file from filepath2 and prints results to the console
// save [specified compare...] - compares files from given compare's parameters and gives a txt file with the results of comparison to the user
// set_accuracy [acc] - sets accuracy as acc
// save_as [filepath] [specified compare...]
// exit - exits the program
// quit - exits the program
// q - exits the program