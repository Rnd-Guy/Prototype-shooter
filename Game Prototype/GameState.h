#pragma once
#include "SFMLIncludes.h"
#include "Game.h"

#include <string>

class GameState {
public:
	//virtual ~GameState();
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void enter(std::string string="") = 0; // accepts messages between state changes
	virtual std::string exit() = 0; // used to pass messages between state changes
	virtual void changeGameState(Game::State newState) = 0;
	virtual void terminate() = 0; // cleanup memory before closing
protected:
	//virtual void changeGameState(Game* game, Game::State newState);

	// maybe have a function return a value when it wants to change state
	// or return another value if it wants to exit.
};

