#include "Timer.h"

#include <ctime>

Timer::Timer() :
	activationDelay(0),
	triggerTime(0)
{
}

Timer::Timer(float activationDelay) :
	activationDelay(activationDelay)
{
		Reset();
}

void Timer::SetActivationDelay(float activationDelay)
{
	this->activationDelay = activationDelay;
}

void Timer::Reset()
{
	clock_t currentTime = clock();
	triggerTime = CalculateTriggerTime(currentTime, activationDelay);
}

bool Timer::IsTriggered()
{
	clock_t currentTime = clock();
	return triggerTime <= currentTime;
}

clock_t Timer::CalculateTriggerTime(clock_t currentTime, float activationDelay) const
{
	return currentTime + (clock_t)(CLOCKS_PER_SEC * activationDelay);
}
