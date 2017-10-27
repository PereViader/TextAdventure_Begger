#include "ItemContainer.h"

#include <vector>
#include <assert.h>
#include <iostream>

using namespace std;

ItemContainer::ItemContainer(string name, string description)
	: Item(name,description,Item::Type::ItemContainer)
{
}


ItemContainer::~ItemContainer()
{
}

const vector<Item*> ItemContainer::GetItemsInside() const {
	vector<Entity*> itemsEntity = FindAll(Entity::Type::Item);
	vector<Item*> items;
	items.reserve(itemsEntity.size());
	for (Entity* entityItem : itemsEntity) {
		items.push_back((Item*)entityItem);
	}
	return items;
}

void ItemContainer::AddItem(Item * item)
{
	assert(item!=nullptr);
	AttachChild(item);
}

void ItemContainer::Look() const
{
	cout << name << endl;
	cout << description << endl;
	cout << "Inside it:" << endl;
	for (Item* item : GetItemsInside()) {
		cout << item->GetDescription() << endl;
	}
}

Item * ItemContainer::Clone() const
{
	return new ItemContainer(*this);
}
