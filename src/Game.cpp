#include "Game.h"
#include "GameState.h"
// the following includes are required to avoid cyclic inclusion
#include "MenuState.h"
#include "PlayState.h"
#include "PausedState.h"
#include "VictoryState.h"
#include "DefeatState.h"






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
	gameStateVector.push_back(std::make_shared<VictoryState>(this, window));
	gameStateVector.push_back(std::make_shared<DefeatState>(this, window));

}


void Game::changeState(State newState) {
	if (newState == end) {
		currentGameState = newState;
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
	for (auto i = 0; i < gameStateVector.size(); ++i) {
		(*gameStateVector[i]).terminate();
	}
	gameStateVector.empty();
	window->close();
	
}
