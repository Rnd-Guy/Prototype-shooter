#pragma once

#include "GameState.h"
#include "ResourceComponent.h"

class MenuState : public GameState {
public:
	MenuState(Game* gamePointer, sf::RenderWindow* window);
	virtual void handleInput() override;
	virtual void update() override;
	virtual void render() override;
	virtual void enter(std::string string="") override;
	virtual std::string exit() override;
	virtual void changeGameState(Game::State newState);	
	virtual void terminate();
	

private:
	Game* gamePointer; // used to change game state
	int menuSelection; // is it on play or quit? 0 for play, 1 for quit
	sf::RenderWindow* window; 
	ResourceComponent resourceComponent;
	sf::Sprite background;
	sf::Sprite selectionRectangle;
};