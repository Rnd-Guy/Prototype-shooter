

// #include <vld.h> //(visual leak detector, used to check for memory leaks)
#include "Game.h"
#include <Windows.h>

// windows application
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow) {
// console application
int main() {
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Prototype");
	window.setFramerateLimit(60);
	Game game(&window);


	game.initialise();

	while (game.isRunning()) {
		game.handleInput();
		game.update();
		game.render();
	}
}