#include "VictoryState.h"



VictoryState::VictoryState(Game * gamePointer, sf::RenderWindow * window) {
	this->gamePointer = gamePointer;
	this->window = window;



	resourceComponent.initialise("VictoryState");
	victoryScreen.setTexture(*(resourceComponent.getTexture("victoryScreen")));
}

void VictoryState::handleInput() {
	sf::Event event;
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			changeGameState(Game::end);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Z)
			{
				changeGameState(Game::menu);
			}
			break;
		default:
			break;
		}
	}
}

void VictoryState::enter(std::string string) {

}

void VictoryState::update() {

}

void VictoryState::render() {
	window->draw(victoryScreen);
}

void VictoryState::changeGameState(Game::State newState) {
	gamePointer->changeState(newState);
}

void VictoryState::terminate() {

}

std::string VictoryState::exit() {
	return "";
}