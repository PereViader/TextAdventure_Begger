#pragma once

#include <string>
#include <vector>

using namespace std;

class Entity
{

public:
	enum class Type {
		player,
		item,
		room,
		exit
	};

	Entity();
	virtual ~Entity();

	void ChangeParentTo(Entity*);


	virtual void Look() const = 0;
	virtual void Update() = 0;

	Entity::Type GetEntityType() const;
	string GetName() const;
	string GetDescription() const;

	vector<Entity*> FindAll(Entity::Type) const;
	vector<Entity*> FindAll(const string&,Entity::Type) const;
	Entity* Find(Entity::Type) const;
	Entity* Find(const string&, Entity::Type) const;
	void Deatach(Entity*);

protected:
	Entity::Type entityType;
	string name;
	string description;

	Entity* parentEntity;
	vector<Entity*> childEntities;
};

