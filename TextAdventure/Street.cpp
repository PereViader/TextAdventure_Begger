#include "Street.h"

#include <assert.h>


Street::Street(string name, string description, float playerBegSuccessRate) : 
	playerBegSuccessRate(playerBegSuccessRate),
	Room(name,description,Room::Type::Street)
{
	assert(playerBegSuccessRate >= 0.0f && playerBegSuccessRate <= 1.0f);
}

Street::~Street()
{
}

float Street::GetPlayerBegSuccessRate() const
{
	return playerBegSuccessRate;
}

