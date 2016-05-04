#include "Game.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PausedState.h"

Game::Game(sf::RenderWindow* window) {
	this->window = window;
	//menuState(this, window);
	//playState(this, window);
	//pausedState(this, window, &playState);


}

void Game::initialise() {
	currentGameState = menu;
	gameRunning = true;
	gameStateVector.push_back(std::make_shared<MenuState>(this, window));
	gameStateVector.push_back(std::make_shared<PlayState>(this, window));
	gameStateVector.push_back(std::make_shared<PausedState>(this, window, gameStateVector[1]));


}


void Game::changeState(State newState) {
	if (newState == end) {
		terminate();
		return;
	}

	// pass message from old state to new state if any (eg whether or not to reset playstate)
	std::string message = gameStateVector[currentGameState]->exit();
	currentGameState = newState;
	gameStateVector[currentGameState]->enter(message);

	
}

bool Game::isRunning() {
	return gameRunning;
}

void Game::handleInput() {
	if (currentGameState != end) gameStateVector[currentGameState]->handleInput();
}

void Game::update() {
	if (currentGameState != end) gameStateVector[currentGameState]->update();
}

void Game::render() {
	if (currentGameState != end) {


		window->clear();
		gameStateVector[currentGameState]->render();
		window->display();
	}
}

void Game::terminate() {
	gameRunning = false;

	for (auto i = 0; i < 3; ++i) {
		(*gameStateVector[i]).terminate();
	}
		
	window->close();

	
}
