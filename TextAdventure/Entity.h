#pragma once

#include <string>
#include <vector>

#include "Globals.h"

using namespace std;

class Entity
{
public:
	enum class Type {
		Creature,
		Item,
		Room,
		Exit
	};

	virtual ~Entity();

	virtual void Look() const;
	virtual Frame_Return Update();

	void ChangeParentTo(Entity*);
	void Deattach(Entity*);
	void Attach(Entity*);

	Entity::Type GetEntityType() const;
	string GetName() const;
	string GetDescription() const;

	vector<Entity*> FindAll(Entity::Type) const;
	vector<Entity*> FindAll(const string&,Entity::Type) const;
	Entity* Find(Entity::Type) const;
	Entity* Find(const string&, Entity::Type) const;


protected:
	Entity(string name, string description, Entity::Type entityType);

	Entity::Type entityType;
	string name;
	string description;

	Entity* parentEntity;
	vector<Entity*> childEntities;
};

