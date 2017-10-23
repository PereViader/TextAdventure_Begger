#include "ItemContainer.h"

#include <vector>
#include <assert.h>

using namespace std;

ItemContainer::ItemContainer(string name, string description)
	: Item(name,description,Item::Type::ItemContainer)
{
}


ItemContainer::~ItemContainer()
{
}

const vector<Item*> ItemContainer::GetItemsInside() const {
	vector<Item*> items;
	items.reserve(childEntities.size());
	for (vector<Entity*>::const_iterator it = childEntities.cbegin(); it != childEntities.cend(); ++it) {
		items.push_back((Item*)(*it));
	}
	return items;
}

void ItemContainer::AddItem(Item * item)
{
	assert(item!=nullptr);
	AttachChild(item);
}
