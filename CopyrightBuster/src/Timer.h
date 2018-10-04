#pragma once

#include <chrono>

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start;

	Timer();
	~Timer();
};