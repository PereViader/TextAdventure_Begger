#include "Item.h"

#include <string>

using namespace std;

Item::Item(string name, string description, Item::Type itemType) : itemType(itemType), Entity(name, description, Entity::Type::Item)
{
}

Item::Type Item::GetItemType() const
{
	return itemType;
}
