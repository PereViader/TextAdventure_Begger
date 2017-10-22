#pragma once

#include <ctime>

class Time
{
public:
	static void Reset();
	static void UpdateClock();
	static float GetDeltaTime();
	
private:
	static clock_t previousTime;
	static float deltaTime;
};

