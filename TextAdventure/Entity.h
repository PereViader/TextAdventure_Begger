#pragma once

#include <string>

using namespace std;

enum EntityType {
	Player,
	Item,
	Room,

};

class Entity
{
public:
	Entity();
	virtual ~Entity();

protected:
	EntityType entityType;
	string name;
	string description;


};

