#include "PlayState.h"
#include "Bullet.h"
#include "Beam.h"

PlayState::PlayState(Game* gamePointer, sf::RenderWindow* window) : 
	bullets(), 
	beams(),
	player(window, bullets, beams), // initialise player, as it has no default constructor
	boss(window, bullets, beams, &player) 
{
	this->gamePointer = gamePointer;
	this->window = window;

	// load up sprite and textures
	resourceComponent.initialise("PlayState");

	// Load up all bullet textures before game starts to prevent loading 
	//   textures mid-play
	Bullet::resourceComponent.initialise("Bullet"); // static
	Beam::resourceComponent.initialise("Beam"); // static

	blackBackground.setTexture(*(resourceComponent.getTexture("blackBackground")));
	orangeOverlay.setTexture(*(resourceComponent.getTexture("orangeOverlay")));

	
}

void PlayState::handleInput()
{
	// event based input
	sf::Event event;
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			changeGameState(Game::end);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				changeGameState(Game::pause);
			}
			break;
		default:
			break;
		}
	}

	
	// polling based input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		player.moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		player.moveRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		player.moveUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		player.moveDown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		player.shoot();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		player.shift();
	}


}

void PlayState::update()
{
	player.update();
	boss.update();
	// bullets 
	for (auto i = 0; i < bullets.size(); ++i) {
		bullets[i]->update();
		// check for boss collisions using bounding boxes (rectangles)
		if (bullets[i]->damageBoss) {
			// damage blue
			if (bullets[i]->getRectHitBox().intersects(boss.getBlueHitBox())) {
				bullets[i]->collision();
				boss.damageBlue(bullets[i]->damage);
				player.damageBlue(bullets[i]->damage);

			}
			// damage red
			if (bullets[i]->getRectHitBox().intersects(boss.getRedLeftHitBox()) ||
				bullets[i]->getRectHitBox().intersects(boss.getRedRightHitBox())) {
				bullets[i]->collision();
				boss.damageRed(bullets[i]->damage);
				player.damageRed(bullets[i]->damage);
			}
			// damage yellow
			if (bullets[i]->getRectHitBox().intersects(boss.getYellowLeftHitBox()) ||
				bullets[i]->getRectHitBox().intersects(boss.getYellowRightHitBox())) {
				bullets[i]->collision();
				boss.damageYellow(bullets[i]->damage);
				player.damageYellow(bullets[i]->damage);
			}


		}
		// check for player collisions using distance for more precision
		if (bullets[i]->damagePlayer) {
			if (bullets[i]->getDistanceFromPoint(player.getX(), player.getY()) < bullets[i]->getRadius() + player.getHitBoxRadius()) {
				bullets[i]->collision();
				player.damaged(bullets[i]->damage);
			}
		}


	}




	// cleanup bullets
	{
		int i = 0;
		while (i < bullets.size()) {
			if ((*bullets[i]).deleteFlag) bullets.erase(bullets.begin() + i);
			else ++i;
		}
	}

	// beams
	for (auto i = 0; i < beams.size(); ++i) {
		beams[i]->update();
		// check for boss collisions
		// to be done later


		// check for player collisions, using player's recthitbox
		if (beams[i]->damagePlayer) {
			if (beams[i]->checkCollision(player.getRectHitbox()) == true) {
				player.damaged(beams[i]->damage);
			}
		}
	}
	// cleanup beams
	{
		int i = 0;
		while (i < beams.size()) {
			if (beams[i]->deleteFlag) beams.erase(beams.begin() + i);
			else ++i;
		}
	}




}

void PlayState::render()
{

	window->draw(blackBackground);
	// game layer
	for (auto i = 0; i < beams.size(); ++i) {
		(*beams[i]).render();
	}
	for (auto i = 0; i < bullets.size(); ++i) {
		(*bullets[i]).render();
	}
	boss.render();
	player.renderGame();
	// bullets



	// overlay layer
	window->draw(orangeOverlay);
	player.renderOverlay();

}

void PlayState::enter(std::string string)
{
	if (string == "reset") {
		reset();
	}
}

std::string PlayState::exit()
{
	return std::string();
}

void PlayState::changeGameState(Game::State newState) {
	gamePointer->changeState(newState);
}

void PlayState::reset() {
	player.reset();
	boss.reset();
	bullets.clear();
	beams.clear();
}

void PlayState::terminate() {
	bullets.clear();
	beams.clear();
}