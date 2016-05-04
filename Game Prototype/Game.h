#pragma once

#include <vector>
#include <memory>
#include "SFMLIncludes.h"

class GameState;

class Game {
public:
	Game(sf::RenderWindow* window);

	enum State {
		menu = 0,
		play = 1,
		pause = 2,
		end = 3
	};

	void initialise();
	bool isRunning();
	void changeState(State newState);
	void handleInput();
	void update();
	void render();
	void terminate();
private:
	sf::RenderWindow* window;
	State currentGameState;
	std::vector<std::shared_ptr<GameState> > gameStateVector;

	bool gameRunning;
};