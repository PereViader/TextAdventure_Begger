#pragma once

#include "Item.h"

class Food :
	public Item
{
public:
	Food(string name, string description, unsigned int energy);

	unsigned int GetEnergy() const;

private:
	unsigned int energy;

	// Inherited via Item
	virtual Item * Clone() const override;
};

