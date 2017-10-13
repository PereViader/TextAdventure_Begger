#include "Entity.h"

#include <algorithm>
#include <iostream>

using namespace std;

Entity::Entity(string name, string description, Entity::Type entityType) : name(name), description(description), entityType(entityType)
{
}

Entity::~Entity()
{
}

void Entity::Look() const
{
	cout << this->name << endl;
	cout << this->description << endl;
	for (vector<Entity*>::const_iterator it = childEntities.cbegin(); it != childEntities.cend(); it++) {
		(*it)->Look();
	}
}

Frame_Return Entity::Update()
{
	return Frame_Return::Continue;
}

Entity::Type Entity::GetEntityType() const {
	return entityType;
}

string Entity::GetName() const {
	return name;
}

string Entity::GetDescription() const {
	return description;
}

void Entity::ChangeParentTo(Entity * newParent)
{
	if ( parentEntity != nullptr ) {
		parentEntity -> Deattach(this);
	}
	newParent -> Attach(this);
}

vector<Entity*> Entity::FindAll(Entity::Type entityType) const
{
	vector<Entity*> entities;
	for (vector<Entity*>::const_iterator it = childEntities.begin(); it != childEntities.end(); ++it) {
		Entity * currentEntity = *it;
		if (currentEntity->entityType == entityType) {
			entities.push_back(*it);
		}
	}
	return entities;
}

vector<Entity*> Entity::FindAll(const string & name, Entity::Type entityType) const
{
	vector<Entity*> entities;
	for (vector<Entity*>::const_iterator it = childEntities.begin(); it != childEntities.end(); ++it) {
		Entity * currentEntity = *it;
		if (currentEntity->entityType == entityType &&
			currentEntity->name.compare(name) == 0) {
			entities.push_back(*it);
		}
	}
	return entities;
}

Entity * Entity::Find(Entity::Type entityType) const
{
	for (vector<Entity*>::const_iterator it = childEntities.begin(); it != childEntities.end(); ++it) {
		Entity * currentEntity = *it;
		if (currentEntity->entityType == entityType) {
			return currentEntity;
		}
	}
	return nullptr;
}

Entity * Entity::Find(const string & name, Entity::Type entityType) const
{
	for (vector<Entity*>::const_iterator it = childEntities.cbegin(); it != childEntities.cend(); ++it) {
		Entity * currentEntity = *it;
		if (currentEntity->entityType == entityType && 
			currentEntity->name.compare(name) == 0) {
			return currentEntity;
		}
	}
	return nullptr;
}

void Entity::Deattach(Entity* entity) {
	if (entity != nullptr && entity -> parentEntity == this) {
		childEntities.erase(remove(parentEntity->childEntities.begin(), parentEntity->childEntities.end(), entity));
		entity -> parentEntity = nullptr;
	}
}

void Entity::Attach(Entity* entity) {
	if (entity != nullptr) {
		entity -> parentEntity = this;
		childEntities.push_back(entity);
	}
}
