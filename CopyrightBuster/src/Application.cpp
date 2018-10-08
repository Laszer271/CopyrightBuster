#include "Raport.h"
#include <chrono>
#include <string>
#include "Timer.h"
#include "FileProcessing.h"

#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h> 

void Test(unsigned int x);

using namespace std::string_literals;

int main()
{


	int WINAPI WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	std::vector<std::string> vec;
	vec.reserve(1);

	vec.emplace_back("clip"s);

	for (int i = 0; i < 1; i++)
	{
		Timer test;
		convertToTxt("C:/Users/Lasze/Downloads/4_IJHMT_2017.pdf"s, "-"s + vec[i], "./Files/"s + vec[i] + "/4_IJHMT_2017.txt"s);
		convertToTxt("C:/Users/Lasze/Downloads/6_HMT_2016.pdf"s, "-"s + vec[i], "./Files/"s + vec[i] + "/6_HMT_2016.txt"s);
		convertToTxt("C:/Users/Lasze/Downloads/7_ETFS__2015.pdf"s, "-"s + vec[i], "./Files/"s + vec[i] + "/7_ETFS__2015.txt"s);
	}

	//Test(1000);

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