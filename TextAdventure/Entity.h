#pragma once

#include <string>
#include <vector>


using namespace std;



class Entity
{
public:
	enum Type {
		player,
		item,
		room
	};

	Entity();
	virtual ~Entity();

	Entity::Type GetEntityType() const;
	string GetName() const;
	string GetDescription() const;

	vector<Entity*> FindAll(Entity::Type) const;
	vector<Entity*> FindAll(const string&,Entity::Type) const;
	Entity* Find(Entity::Type) const;
	Entity* Find(const string&, Entity::Type);


protected:
	Entity::Type entityType;
	string name;
	string description;

	vector<Entity*> associatedEntities;
};

