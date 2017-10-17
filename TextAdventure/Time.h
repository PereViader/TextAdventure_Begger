#pragma once

#include <ctime>

class Time
{
public:
	static void Reset();
	static void UpdateClock();
	static double GetDeltaTime();
	
private:
	static clock_t previousTime;
	static double deltaTime;
};

