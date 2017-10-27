#include "Food.h"

Food::Food(string name, string description, unsigned int energy) : 
	energy(energy), 
	Item(name, description, Item::Type::Food)
{
}

unsigned int Food::GetEnergy() const
{
	return energy;
}

Item * Food::Clone() const
{
	return new Food(*this);
}
