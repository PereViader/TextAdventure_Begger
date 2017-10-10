#include "Shop.h"

#include "Item.h"
#include "Player.h"

#include <assert.h>
#include <map>

Shop::Shop()
{
}


Shop::~Shop()
{
}

void Shop::AddItem(Item* item, const int& price) {
	item->ChangeParentTo(this);
	itemCost[item] = price;
}


/*
Sells the specified to the player. Removes the player's money amount accordingly.
Returns if the player has bought or couldn't buy the item.

Pre: The shop is the owner of the item.
*/
bool Shop::SellItemToPlayer(Player* player, Item* item) {
	bool itemWasBought = false;
	int itemPrice;
	bool shopHasItem = GetPriceForItem(item, itemPrice);
	assert(shopHasItem);
	if (shopHasItem) {
		if (player->RemoveMoney(itemPrice)) {
			itemWasBought = true;
			item->ChangeParentTo(player);
			itemCost.erase(item);
		}
	}
	return itemWasBought;
}

bool Shop::GetPriceForItem(const Item* item, int& price) const
{
	map <const Item*, int>::const_iterator it = itemCost.find(item);
	bool hasItem = it != itemCost.cend();
	if (hasItem) {
		price = it->second;
	}
	return hasItem;
}


