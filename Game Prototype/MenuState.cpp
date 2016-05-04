#include "MenuState.h"

MenuState::MenuState(Game* gamePointer, sf::RenderWindow* window) {
	this->gamePointer = gamePointer;
	this->window = window;

	// load up sprite and textures
	resourceComponent.initialise("MenuState");
	background.setTexture(*(resourceComponent.getTexture("background")));
	selectionRectangle.setTexture(*(resourceComponent.getTexture("selectionRectangle")));
	menuSelection = 0;

}

void MenuState::handleInput() {
	// event based input
	sf::Event event;
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			changeGameState(Game::end);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Up){
				menuSelection = 0;
			}
			if (event.key.code == sf::Keyboard::Down) {
				menuSelection = 1;
			}
			if (event.key.code == sf::Keyboard::Z)
			{
				if (menuSelection == 0) {
					changeGameState(Game::play);
				}
				if (menuSelection == 1) {
					changeGameState(Game::end);
				}
			}
			break;
		default:
			break;
		}
		
	}

	// polling based input goes here if there is any
	//   none for this state
}

void MenuState::update() {
	if (menuSelection == 0) {
		selectionRectangle.setPosition(540, 299);
	}
	if (menuSelection == 1) {
		selectionRectangle.setPosition(540, 385);
	}
}

void MenuState::render() {

	window->draw(background);
	window->draw(selectionRectangle);

}

void MenuState::enter(std::string string) {
	menuSelection = 0;
}

std::string MenuState::exit() {
	// when going to playstate from main menu, reset playstate
	return "reset";
}

void MenuState::changeGameState(Game::State newState) {
	gamePointer->changeState(newState);
}

void MenuState::terminate() {

}