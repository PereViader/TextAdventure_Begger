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

void Shop::SellItemToPlayer(Player* player, Item* item) {
	int itemPrice;
	bool shopHasItem = GetPriceForItem(item, itemPrice);
	assert(shopHasItem);
	if (shopHasItem) {
		if (player->RemoveMoney(itemPrice)) {
			item->ChangeParentTo(player);
			itemCost.erase(item);
		}
	}
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


