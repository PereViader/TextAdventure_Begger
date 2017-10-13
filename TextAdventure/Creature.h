#pragma once

#include "Entity.h"

class Creature :
	public Entity
{
public:
	enum class Type{
		Player
	};

	const Creature::Type GetCreatureType() const;

protected:
	Creature(string name, string description, Creature::Type creatureType);

private:
	Creature::Type creatureType;
};

