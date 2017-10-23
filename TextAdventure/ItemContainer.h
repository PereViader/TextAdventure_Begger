#pragma once
#include "Item.h"

#include <vector>

using namespace std;

class ItemContainer :
	public Item
{
public:
	ItemContainer(string name, string description);
	~ItemContainer();

	const vector<Item*> GetItemsInside() const;
	void AddItem(Item* item);
};

