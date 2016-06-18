#pragma once

#include "GameState.h"
#include "ResourceComponent.h"

class DefeatState : public GameState {
public:
	DefeatState(Game* gamePointer, sf::RenderWindow* window);
	virtual void handleInput();
	virtual void update();
	virtual void render();
	virtual void enter(std::string string = "");
	virtual std::string exit();
	virtual void terminate();
	virtual void changeGameState(Game::State newState);


private:
	Game* gamePointer;
	sf::RenderWindow* window;
	ResourceComponent resourceComponent;

	sf::Sprite defeatScreen;



};