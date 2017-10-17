#include "Time.h"
#include <iostream>

double Time::deltaTime = 0;
clock_t Time::previousTime = clock();

void Time::Reset()
{
	previousTime = clock();
	deltaTime = 0;
}

void Time::UpdateClock()
{
	clock_t presentTime = clock();
	deltaTime = (double)(presentTime - previousTime) / CLOCKS_PER_SEC;
	previousTime = presentTime;
}

double Time::GetDeltaTime()
{
	return deltaTime;
}
