#pragma once

#include "Room.h"

#include <map>

class Item;

class Player;

class Shop :
	public Room
{
public:
	Shop(string name, string description);
	virtual ~Shop();

	void AddItem(Item*, const int& price);
	bool SellItemToPlayer(Player*, Item*);

	bool GetPriceForItem(const Item *, int&) const;

private:
	map<const Item*, int> itemCost;
};

