#include "Item.h"

#include <string>
#include <iostream>

using namespace std;

Item::Item(string name, string description, Item::Type itemType) : 
	itemType(itemType), 
	Entity(name, description, Entity::Type::Item)
{
}

Item::Type Item::GetItemType() const
{
	return itemType;
}

void Item::Look() const
{
	cout << description << endl;
}
