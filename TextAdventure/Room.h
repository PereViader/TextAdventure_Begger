#pragma once
#include "Entity.h"

#include <vector>

class Exit;

class Room :
	public Entity
{
public:
	enum Type {
		Error,
		Shop,
		Street
	};

	Room();
	virtual ~Room();

	Room::Type GetRoomType() const;
	vector<Exit*> GetExits() const;


	// Inherited via Entity
	virtual void Look() const override;


private:

	Room::Type roomType;
};

