#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
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

vector<Entity*> Entity::FindAll(Entity::Type entityType) const
{
	vector<Entity*> entities;
	for (vector<Entity*>::const_iterator it = associatedEntities.begin(); it != associatedEntities.end(); ++it) {
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
	for (vector<Entity*>::const_iterator it = associatedEntities.begin(); it != associatedEntities.end(); ++it) {
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
	for (vector<Entity*>::const_iterator it = associatedEntities.begin(); it != associatedEntities.end(); ++it) {
		Entity * currentEntity = *it;
		if (currentEntity->entityType == entityType) {
			return currentEntity;
		}
	}
	return NULL;
}

Entity * Entity::Find(const string & name, Entity::Type entityType)
{
	for (vector<Entity*>::const_iterator it = associatedEntities.begin(); it != associatedEntities.end(); ++it) {
		Entity * currentEntity = *it;
		if (currentEntity->entityType == entityType && 
			currentEntity->name.compare(name) == 0) {
			return currentEntity;
		}
	}
	return nullptr;
}
