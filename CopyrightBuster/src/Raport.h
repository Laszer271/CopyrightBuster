#pragma once

#include <iostream>
#include <vector>


class Raport
{
private:
	std::string m_Text;
	std::string m_Filename;
	unsigned int m_Count;

public:
	Raport(const std::string& filepath);

	unsigned int getCount() const;
	void resetCount();

	bool search(const std::string& suspect);
	void compare(const std::string& filepath, unsigned int divider = 1);
	void compareToAll(unsigned int divider = 1);
};

