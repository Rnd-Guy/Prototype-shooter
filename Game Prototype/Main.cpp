#include "Game.h"

//int main()
//{
//	startGame(); // Go to game loop
//
//	return 0;
//}

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