#pragma once

#include <iostream>
#include <vector>


class Raport
{
private:
	std::vector<std::string> m_Paragraphs;
	std::vector<unsigned int> m_Count;

public:
	Raport(const std::string& filepath);

	unsigned int getCount(unsigned int parNumber) const;
	unsigned int getNumOfParagraphs() const;

	void search(const std::string& suspect);
	void compare(const std::string& filepath, unsigned int divider = 1);
};

