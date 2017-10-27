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
	sellableItemPropotypes.push_back(item);
	sellableItemPropotypesPrice[item] = price;
}



void Shop::AddItemToShop(Item* item, const unsigned int price) {
	assert(item);
	item->AttachToParent(this);
	itemCost[item] = price;
}


/*
Sells the specified to the player. Removes the player's money amount accordingly.
Returns if the player has bought or couldn't buy the item.

Pre: The shop is the owner of the item.
*/
bool Shop::SellItemToPlayer(Player* player, Item* item) {
	assert(player);
	assert(item);
	bool itemWasBought = false;
	unsigned int itemPrice;
	bool shopHasItem = GetPriceForItem(item, itemPrice);
	assert(shopHasItem);
	if (shopHasItem) {
		if (player->RemoveMoney(itemPrice)) {
			itemWasBought = true;
			item->AttachToParent(player);
			itemCost.erase(item);
		}
	}
	return itemWasBought;
}

bool Shop::GetPriceForItem(const Item* item, unsigned int & price) const
{
	assert(item);
	map <const Item*, int>::const_iterator it = itemCost.find(item);
	bool hasItem = it != itemCost.cend();
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
		Item* sellableItemPrototype = sellableItemPropotypes.front();
		unsigned int price = sellableItemPropotypesPrice[sellableItemPrototype];
		cout << "Added item to shop " << sellableItemPrototype->GetName() << endl;
		Item* itemToSell = sellableItemPrototype->Clone();
		AddItemToShop(itemToSell, price);

		sellableItemPropotypes.pop_front();
		sellableItemPropotypes.push_back(sellableItemPrototype);
	}
}