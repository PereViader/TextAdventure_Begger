#include <iostream>
#include <chrono>
#include <thread>

#include "Game.h"

int main(void) {
	Game game;
	game.Execute();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return 0;
}