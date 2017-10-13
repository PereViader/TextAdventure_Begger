#pragma once

#include "Entity.h"

class Item :
	public Entity
{
public:
	enum class Type {
		Food,
		Object,
	};

	Item::Type GetItemType() const;

protected:	
	Item(string name, string description, Item::Type itemType);

private:
	Item::Type itemType;

};

