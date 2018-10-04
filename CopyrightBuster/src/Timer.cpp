#include "Timer.h"
#include "iostream"

Timer::Timer()
	: start(std::chrono::high_resolution_clock::now()) {}

Timer::~Timer()
{
	std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;

	double ms = duration.count() * 1000.0;
	std::cout << " duration: " << ms << " ms\n" << std::endl;
}