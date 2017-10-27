#include "Entity.h"

#include <algorithm>
#include <iostream>

using namespace std;

Entity::Entity(string name, string description, Entity::Type entityType) : name(name), description(description), entityType(entityType)
{
}

Entity::Entity(const Entity & other) :
	entityType(other.entityType),
	name(other.name),
	description(other.description),
	parentEntity(nullptr),
	isDead(other.isDead)
{
	for (Entity * entity : other.childEntities) {
		Entity * childEntity = new Entity(*entity);
		AttachChild(childEntity);
	}
}

Entity::~Entity()
{
	DeatachFromParent();

	while (childEntities.size() > 0) {
		Entity * entity = childEntities.back();
		childEntities.pop_back();
		delete entity;
	}
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

const Entity::Type Entity::GetEntityType() const {
	return entityType;
}

const string Entity::GetName() const {
	return name;
}

const string Entity::GetDescription() const {
	return description;
}

vector<Entity*> Entity::GetChilds() const
{
	return childEntities;
}

Entity * Entity::GetParent() const
{
	return parentEntity;
}

void Entity::AttachToParent(Entity * newParent)
{
	DeatachFromParent();
	
	if (newParent != nullptr)
		newParent -> AttachChild(this);
}

void Entity::DeatachFromParent()
{
	if (parentEntity != nullptr)
		parentEntity->DeattachChild(this);
}

vector<Entity*> Entity::FindAll(Entity::Type entityType) const
{
	vector<Entity*> entities;
	for (vector<Entity*>::const_iterator it = childEntities.begin(); it != childEntities.end(); ++it) {
		Entity * currentEntity = *it;
		if (currentEntity->entityType == entityType) {
			entities.push_back(currentEntity);
		}
	}
	return entities;
}

vector<Entity*> Entity::FindAll(const string & name) const
{
	vector<Entity*> entities;
	for (vector<Entity*>::const_iterator it = childEntities.begin(); it != childEntities.end(); ++it) {
		Entity * currentEntity = *it;
		if (currentEntity->name == name){
			entities.push_back(currentEntity);
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
			currentEntity->name == name) {
			entities.push_back(currentEntity);
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

Entity * Entity::Find(const string & name) const
{
	for (vector<Entity*>::const_iterator it = childEntities.cbegin(); it != childEntities.cend(); ++it) {
		Entity * currentEntity = *it;
		if (currentEntity->name == name) {
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
			currentEntity->name == name) {
			return currentEntity;
		}
	}
	return nullptr;
}

void Entity::Delete()
{
	isDead = true;
}

bool Entity::IsDead()
{
	return isDead;
}

void Entity::DeattachChild(Entity* entity) {
	if (entity != nullptr && entity -> parentEntity == this) {
		childEntities.erase(remove(childEntities.begin(), childEntities.end(), entity), childEntities.end());
		entity -> parentEntity = nullptr;
	}
}

void Entity::AttachChild(Entity* entity) {
	if (entity != nullptr) {
		if (entity->parentEntity != nullptr) {
			entity->parentEntity->DeattachChild(entity);
		}
		entity -> parentEntity = this;
		childEntities.push_back(entity);
	}
}