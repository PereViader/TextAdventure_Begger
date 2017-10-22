#pragma once

#include <string>
#include <vector>

#include "Globals.h"

using namespace std;

class Entity
{
public:
	enum class Type {
		World,
		Creature,
		Item,
		Room,
		Exit
	};

	virtual ~Entity();

	virtual void Look() const;
	virtual Frame_Return Update();

	void AttachToParent(Entity*);
	void DeatachFromParent();
	void DeattachChild(Entity*);
	void AttachChild(Entity*);

	const Entity::Type GetEntityType() const;
	const string GetName() const;
	const string GetDescription() const;
	vector<Entity*> GetChilds() const;
	Entity* GetParent() const;

	vector<Entity*> FindAll(Entity::Type) const;
	vector<Entity*> FindAll(const string&) const;
	vector<Entity*> FindAll(const string&,Entity::Type) const;
	Entity* Find(Entity::Type) const;
	Entity* Find(const string&) const;
	Entity* Find(const string&, Entity::Type) const;


protected:
	Entity(string name, string description, Entity::Type entityType);

	const Entity::Type entityType;
	const string name;
	const string description;

	Entity* parentEntity;
	vector<Entity*> childEntities;
};

