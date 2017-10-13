#pragma once

#include "Room.h"

#include <string>

using namespace std;

class Street :
	public Room
{
public:
	Street(string name, string description);
	~Street();
};

