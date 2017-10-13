#include "Creature.h"
#include "PlayerInput.h"

class PlayerAction;
class Room;


class Player :
	public Creature
{
public:
	Player(Room* startingRoom);
	~Player();
	
	unsigned int GetMoney();
	bool RemoveMoney(const unsigned int&);

	// Inherited via Creature
	virtual void Look() const override;
	virtual void Update() override;
	
	
	//Player Actions
	void ActionBeg(const PlayerAction&);
	void ActionLook(const PlayerAction&);
	void ActionInventory(const PlayerAction&);
	void ActionBuy(const PlayerAction&);
	void ActionTake(const PlayerAction&);
	void ActionGo(const PlayerAction&);
	void ActionEat(const PlayerAction&);
	
private:

	Room * currentRoom;
	unsigned int hunger;
	unsigned int money;
	
	PlayerInput * playerInput;
};

