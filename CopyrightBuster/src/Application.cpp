#include "Raport.h"
#include <chrono>
#include <string>
#include "Timer.h"

void Test(unsigned int x);

int main()
{
	Test(1000);

	std::cin.get();
}

void Test(unsigned int x)
{
	Timer time;

	for (int i = 0; i < x; i++) {
		Raport rap("Files/Files.txt");
		rap.compare("Files/File2.txt", 5);
	}

	//unsigned int count = rap.getNumOfParagraphs();


	//for (unsigned int i = 0; i < count; i++)
		//std::cout << rap.getCount(i) << "\n";
}