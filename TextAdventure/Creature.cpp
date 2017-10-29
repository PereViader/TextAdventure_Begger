#include "Creature.h"
#include "Room.h"

#include <assert.h>

const Creature::Type Creature::GetCreatureType() const
{
	return creatureType;
}

Creature::Creature(string name, string description, Creature::Type creatureType) : 
	creatureType(creatureType), 
	Entity(name, description,Entity::Type::Creature)
{
}

Room * Creature::GetCurrentRoom() const
{
	return (Room*)parentEntity;
}

void Creature::Move(Room * destination)
{
	assert(destination);
	AttachToParent(destination);
}
