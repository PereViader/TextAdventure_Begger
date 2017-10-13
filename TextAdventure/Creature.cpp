#include "Creature.h"

const Creature::Type Creature::GetCreatureType() const
{
	return creatureType;
}

Creature::Creature(string name, string description, Creature::Type creatureType) : creatureType(creatureType), Entity(name, description,Entity::Type::Creature)
{
}
