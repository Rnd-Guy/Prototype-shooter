#include "DefeatState.h"



DefeatState::DefeatState(Game * gamePointer, sf::RenderWindow * window) {
	this->gamePointer = gamePointer;
	this->window = window;



	resourceComponent.initialise("DefeatState");
	defeatScreen.setTexture(*(resourceComponent.getTexture("defeatScreen")));
}

void DefeatState::handleInput() {
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

void DefeatState::enter(std::string string) {

}

void DefeatState::update() {

}

void DefeatState::render() {
	window->draw(defeatScreen);
}

void DefeatState::changeGameState(Game::State newState) {
	gamePointer->changeState(newState);
}

void DefeatState::terminate() {

}

std::string DefeatState::exit() {
	return "";
}