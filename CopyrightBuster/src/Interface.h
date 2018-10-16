#pragma once
#include <string>

void menu();
void help();
//void help(const std::string command);
void filelist();
bool removeFile(const std::string filename);
bool import(const std::string filepath);
bool changeFilename(const std::string filename, const std::string name);
bool changeFilename(unsigned int i, const std::string name);
bool removeFromDatabase(const std::string& filename);
bool compare(const std::string& arg1, const std::string& arg2, const std::string& accuracy);
