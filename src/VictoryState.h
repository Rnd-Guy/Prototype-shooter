#pragma once

#include "GameState.h"
#include "ResourceComponent.h"

class VictoryState : public GameState {
public:
	VictoryState(Game* gamePointer, sf::RenderWindow* window);
	virtual void handleInput();
	virtual void update();
	virtual void render();
	virtual void enter(std::string string="");
	virtual std::string exit();
	virtual void terminate();
	virtual void changeGameState(Game::State newState);


private:
	Game* gamePointer;
	sf::RenderWindow* window;
	ResourceComponent resourceComponent;

	sf::Sprite victoryScreen;



};
/*
Idea: take a pointer to player and a pointer to boss.
Do i want to let the player and boss animate themselves?
Ignore animations for now, just render playState
Handle victory animation and credits? maybe

First have a temporary screen, a placeholder for winning, eg credits




*/