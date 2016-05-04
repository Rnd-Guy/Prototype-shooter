#include "PausedState.h"

PausedState::PausedState(Game* gamePointer, sf::RenderWindow* window, std::shared_ptr<GameState> playStatePointer) {
	this->gamePointer = gamePointer;
	this->window = window;
	this->playStatePointer = playStatePointer;

	// load up sprite and textures
	resourceComponent.initialise("PausedState");
	greyTint.setTexture(*(resourceComponent.getTexture("greyTint")));
	pauseMenu.setTexture(*(resourceComponent.getTexture("pauseMenu")));
	selectionRectangle.setTexture(*(resourceComponent.getTexture("selectionRectangle")));

	pauseMenu.setPosition(sf::Vector2f(200, 200));


}

void PausedState::handleInput() {
	// event based input
	sf::Event event;
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			changeGameState(Game::end);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Up) {
				if (menuSelection > 0) --menuSelection;
			}
			if (event.key.code == sf::Keyboard::Down) {
				if (menuSelection < 2) ++menuSelection;
			}
			if (event.key.code == sf::Keyboard::Escape) {
				menuSelection = 0;
				changeGameState(Game::play);
			}

			if (event.key.code == sf::Keyboard::Z)
			{
				if (menuSelection == 0) {
					// resume playing
					changeGameState(Game::play);
				}
				if (menuSelection == 1) {
					// retry
					changeGameState(Game::play);
				}
				if (menuSelection == 2) {
					// back to main menu
					changeGameState(Game::menu);
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

void PausedState::update() {
	if (menuSelection == 0) {
		selectionRectangle.setPosition(280, 280);
	}
	if (menuSelection == 1) {
		selectionRectangle.setPosition(280, 315);
	}
	if (menuSelection == 2) {
		selectionRectangle.setPosition(280, 350);
	}
}

void PausedState::render() {

	playStatePointer->render(); // draw play area in the background
	window->draw(greyTint);
	window->draw(pauseMenu);
	window->draw(selectionRectangle);
	
}

void PausedState::enter(std::string string) {
	menuSelection = 0;
}

std::string PausedState::exit() {
	if (menuSelection == 1) {
		// retry
		return "reset";
	}
	else {
		return "";
	}
}

void PausedState::changeGameState(Game::State newState) {
	gamePointer->changeState(newState);
}

void PausedState::terminate() {

}