#pragma once

#include "Entity.h"

class Item :
	public Entity
{
public:
	enum class Type {
		Food,
		Object,
		ItemContainer,
	};

	Item::Type GetItemType() const;

	void Look() const override ;
	virtual Item* Clone() const = 0;
protected:	
	Item(string name, string description, Item::Type itemType);

private:
	Item::Type itemType;

};

