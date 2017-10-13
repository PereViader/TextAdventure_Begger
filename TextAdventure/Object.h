#pragma once

#include "Item.h"

#include <string>

using namespace std;


class Object :
	public Item
{
public:
	Object(string name, string description);
	~Object();
};

