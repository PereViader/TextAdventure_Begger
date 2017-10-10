#include "Room.h"

#include <map>

class Item;

class Player;

class Shop :
	public Room
{
public:
	Shop();
	virtual ~Shop();

	void AddItem(Item*, const int& price);
	void SellItemToPlayer(Player*, Item*);

	bool GetPriceForItem(const Item *, int&) const;

private:
	map<const Item*, int> itemCost;
};

