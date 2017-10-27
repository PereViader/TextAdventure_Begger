#include "Object.h"


Object::Object(string name, string description) : Item(name, description, Item::Type::Object)
{
}

Object::~Object()
{
}

Item * Object::Clone() const
{
	return new Object(*this);
}
