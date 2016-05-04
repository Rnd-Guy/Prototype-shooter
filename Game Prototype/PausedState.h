#pragma once

#include "GameState.h"
#include "ResourceComponent.h"
#include <memory>

class PlayState;

class PausedState : public GameState {
public:
	PausedState(Game* gamePointer, sf::RenderWindow* window, std::shared_ptr<GameState> playStatePointer);
	virtual void handleInput() override;
	virtual void update() override;
	virtual void render() override;
	virtual void enter(std::string string = "") override;
	virtual std::string exit() override;
	virtual void changeGameState(Game::State newState);
	virtual void terminate();


private:
	Game* gamePointer; // used to change game state
	std::shared_ptr<GameState> playStatePointer; // used to render the playState under the pause menu
	int menuSelection; // is it on continue, retry or quit
	sf::RenderWindow* window;
	ResourceComponent resourceComponent;
	sf::Sprite greyTint;
	sf::Sprite selectionRectangle;
	sf::Sprite pauseMenu;
};