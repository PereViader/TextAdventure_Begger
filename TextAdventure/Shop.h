#pragma once

#include "Room.h"

#include <map>
#include <list>
#include "Timer.h"

class Item;

class Player;

class Shop :
	public Room
{
public:
	Shop(string name, string description);
	virtual ~Shop();

	void AddAsSellableItemPropotype(Item*, const unsigned int price);

	bool SellItemToPlayer(Player*, Item*);
	bool GetPriceForItem(const Item *, unsigned int & price) const;

	Frame_Return Update() override;

private:
	void AddItemPrototypeToShop(Item*);


private:
	bool IsFull() const;
	void RestockShop();
	Item* GetNextItemToRestock();


	list<Item*> sellableItemPropotypes;
	map<string, unsigned int> sellableItemPropotypesPrice;

	Timer timer;
};

