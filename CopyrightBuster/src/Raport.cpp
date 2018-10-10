#include "Raport.h"

#include <fstream>
#include <string>

#define LINE_FRAGMENT_MIN 35

Raport::Raport(const std::string& filepath)
	: m_Count(0)
{
	std::ifstream file;
	file.open(filepath.c_str());

	std::string rap;

	while (std::getline(file, rap, '\t'))
	{
		m_Text += rap;
	}

	file.close();

	int i = filepath.length();
	for (; filepath[i] != '/'; i--);

	m_Filename = filepath.substr(i + 1);
}

unsigned int Raport::getCount() const
{
	return m_Count;
}

void Raport::resetCount()
{
	m_Count = 0;
}

bool Raport::search(const std::string & suspect)
{

	if ((m_Text.find(suspect)) != std::string::npos)
	{
		m_Count++;
		return true;
	}
	return false;
}

void Raport::compare(const std::string & filepath, unsigned int divider)
{
	if (!divider)
	{
		std::cerr << "Divider can't be zero";
		return;
	}

	std::ifstream file;
	file.open(filepath.c_str());

	std::string line;
	std::string lineFragment;

	unsigned int originalDivider = divider;

	while (std::getline(file, line, '.'))
	{
		divider = originalDivider;

		unsigned int charCount = line.length();

		if (charCount < 10) 
			continue;

		if (charCount < LINE_FRAGMENT_MIN)
		{
			std::getline(file, lineFragment, '.');
			line += lineFragment;
			charCount = line.length();
		}

		unsigned int temp = charCount / divider;

		while (temp < LINE_FRAGMENT_MIN && temp != charCount)
		{
			divider--;
			temp = charCount / divider;
		}

		for (unsigned int offset = 0u; offset != charCount; )
		{
			unsigned int offsetBeggining = offset + 1;
			offset += temp;

			while (offset < charCount && line[offset] != ' ')
				offset++;

			if (offset > charCount || charCount - offset < LINE_FRAGMENT_MIN)
				offset = charCount;

			lineFragment = line.substr(offsetBeggining, offset - offsetBeggining);
			if (this->search(lineFragment))
			{
				std::cout << "Number " << m_Count << ":   " << lineFragment << "\n";
			}
		}
	}
	file.close();
}

using namespace std::string_literals;

void Raport::compareToAll(unsigned int divider)
{
	std::ifstream database("./Files/database.txt");
	std::string filename;
	while (getline(database, filename))
	{
		if (filename != m_Filename)
		{
			std::cout << "\nIn file " << filename << ":\n\n";
			compare("./Files/"s + filename, divider);
			resetCount();
		}
	}
}
