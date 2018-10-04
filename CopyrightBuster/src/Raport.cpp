#include "Raport.h"

#include <fstream>
#include <string>

Raport::Raport(const std::string& filepath)
{
	std::ifstream file;
	file.open(filepath.c_str());

	std::string text;
	std::string paragraph;

	while (std::getline(file, paragraph, '\t'))
	{
		m_Paragraphs.emplace_back(paragraph);
	}

	unsigned int i = m_Paragraphs.size();

	m_Count.reserve(i);

	for (int j = 0; j < i; j++)
		m_Count.emplace_back(0);

	file.close();
}

unsigned int Raport::getCount(unsigned int parNumber) const
{
	return m_Count[parNumber];
}

unsigned int Raport::getNumOfParagraphs() const
{
	return m_Count.size();
}


void Raport::search(const std::string & suspect)
{
	int size = m_Paragraphs.size();

	for (int i = 0; i < size; i++)
	{
		if ((m_Paragraphs[i].find(suspect)) != std::string::npos)
		{
			m_Count[i]++;
		}
	}

	return;
}

void Raport::compare(const std::string & filepath, unsigned int divider)
{
	std::ifstream file;
	file.open(filepath.c_str());

	std::string line;
	std::string lineFragment;

	unsigned int originalDivider = divider;

	while (std::getline(file, line, '.'))
	{
		divider = originalDivider;

		unsigned int charCount = line.size();
		unsigned int temp = charCount / divider;

		while (temp < 25 && temp != charCount)
		{
			divider--;
			temp = charCount / divider;
		}

		for (int i = 0; i < divider; i++)
		{
			lineFragment = line.substr(i * temp, (i + 1) * temp);
			this->search(lineFragment);
		}
	}
	file.close();
}
