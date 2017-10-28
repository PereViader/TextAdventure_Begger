#include "Shop.h"

#include "Item.h"
#include "Player.h"

#include <assert.h>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>

#define SHOP_RESTOCK_TIME_SECONDS 3.0f
#define MAX_SHOP_SIZE 3

using namespace std;

Shop::Shop(string name, string description) : 
	Room(name,description,Room::Type::Shop)
{
		timer.SetActivationDelay(SHOP_RESTOCK_TIME_SECONDS);
}


Shop::~Shop()
{
}

void Shop::AddAsSellableItemPropotype(Item * item, const unsigned int price)
{
	assert(item);
	assert(std::find(sellableItemPropotypes.begin(), sellableItemPropotypes.end(), item) == sellableItemPropotypes.end());
	assert(sellableItemPropotypesPrice.find(item->GetName() == sellableItemPropotypesPrice.cend()));

	sellableItemPropotypes.push_back(item);
	sellableItemPropotypesPrice[item->GetName()] = price;
}



void Shop::AddItemPrototypeToShop(Item* itemPrototype) {
	assert(itemPrototype);
	Item* itemToSell = itemPrototype->Clone();
	AttachChild(itemToSell);
}


/*
Sells the specified to the player. Removes the player's money amount accordingly.
Returns if the player has bought or couldn't buy the item.

Pre: The shop is the owner of the item.
*/
bool Shop::SellItemToPlayer(Player* player, Item* item) {
	assert(player);
	assert(item);
	bool playerGotTheItem = false;
	unsigned int itemPrice;
	bool shopHasPriceForItem = GetPriceForItem(item, itemPrice);
	assert(shopHasItem);
	if (shopHasPriceForItem) {
		if (player->RemoveMoney(itemPrice)) {
			playerGotTheItem = true;
			item->AttachToParent(player);
		}
	}
	else {
		cout << "Shop: This is not our's, you can take it" << endl;
		item->AttachToParent(player);
		playerGotTheItem = true;
	}
	return playerGotTheItem;
}

bool Shop::GetPriceForItem(const Item* item, unsigned int & price) const
{
	assert(item);
	map <string, unsigned int>::const_iterator it = sellableItemPropotypesPrice.find(item->GetName());
	bool hasItem = it != sellableItemPropotypesPrice.cend();
	if (hasItem) {
		price = it->second;
	}
	return hasItem;
}

Frame_Return Shop::Update()
{
	if (timer.IsTriggered()) {
		if (!IsFull()) {
			RestockShop();
		}
		timer.Reset();
	}
	return Frame_Return::Continue;
}

bool Shop::IsFull() const
{
	return FindAll(Entity::Type::Item).size() >= MAX_SHOP_SIZE;
}

void Shop::RestockShop()
{
	if (sellableItemPropotypes.size() > 0) {
		Item* sellableItemPrototype = GetNextItemToRestock();
		AddItemPrototypeToShop(sellableItemPrototype);
	}
}

Item * Shop::GetNextItemToRestock()
{
	assert(sellableItemPropotypes.size() > 0);
	Item* nextItemToRestock = sellableItemPropotypes.front();
	sellableItemPropotypes.pop_front();
	sellableItemPropotypes.push_back(nextItemToRestock);
	return nextItemToRestock;
}
