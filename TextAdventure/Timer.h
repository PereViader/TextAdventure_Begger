#pragma once

#include <ctime>

class Timer
{
public:
	Timer();
	Timer(float activationDelay);

	void SetActivationDelay(float activationDelay);
	
	void Reset();
	bool IsTriggered();


private:
	clock_t CalculateTriggerTime(clock_t currentTime, float activationDelay) const;

	clock_t triggerTime;
	float activationDelay;

};

