#include "PlayState.h"
#include "Bullet.h"
#include "Beam.h"

PlayState::PlayState(Game* gamePointer, sf::RenderWindow* window) : 
	// initialise references and classes with no default constructor
	bullets(), 
	beams(),
	firePattern(window, bullets, beams),
	player(window, bullets, beams, &firePattern), 
	boss(window, bullets, beams, &player, &firePattern)
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
	// should delegate input to the player rather than managing input here

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
			if (event.key.code == sf::Keyboard::A) {
				player.autofire();
			}
			if (event.key.code == sf::Keyboard::D) {
				player.debug();
				boss.debug();
			}
			break;
		
		default:
			break;
		}
	}

	player.storePreviousPosition();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || player.getAutofire() == true) {
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
	firePattern.update();
	for (auto i = 0; i < gameObjects.size(); ++i) {
		gameObjects[i]->update();
	}

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
		if (beams[i]->damageBoss) {
			int hitboxVectorSize = beams[i]->getHitboxVectorSize();
			for (int j = 0; j < hitboxVectorSize; ++j) {
				// damage blue
				if (beams[i]->checkCollision(boss.getBlueHitBox(), j)) {
					boss.damageBlue(beams[i]->damage);
					player.damageBlue(beams[i]->damage);
					break;
				}
				// damage red
				if (beams[i]->checkCollision(boss.getRedLeftHitBox(), j) ||
					beams[i]->checkCollision(boss.getRedRightHitBox(), j)) {
					boss.damageRed(beams[i]->damage);
					player.damageRed(beams[i]->damage);
					break;
				}
				if (beams[i]->checkCollision(boss.getYellowLeftHitBox(), j) ||
					beams[i]->checkCollision(boss.getYellowRightHitBox(), j)) {
					boss.damageYellow(beams[i]->damage);
					player.damageYellow(beams[i]->damage);
					break;
				
				}
			}
		}


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


	// check if boss is dead
	if (boss.getCurrentHP() <= 0) {
		changeGameState(Game::victory);
	}

	// check if player is dead
	if (player.getLives() < 0) { 
		changeGameState(Game::defeat);
	}

}


//__declspec(noinline) void PlayState::render() // testing if this causes pause menu to not show up
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

	// currently gameObjects doesn't actually do anything
	for (auto i = 0; i < gameObjects.size(); ++i) {
		gameObjects[i]->render();
	}

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
	firePattern.reset();
	bullets.clear();
	beams.clear();
}

Player * PlayState::getPlayer()
{
	return &player;
}

Boss * PlayState::getBoss()
{
	return &boss;
}

std::vector<std::unique_ptr<Bullet>>& PlayState::getBullets()
{
	return bullets;
}

std::vector<std::unique_ptr<Beam>>& PlayState::getBeam()
{
	return beams;
}

void PlayState::terminate() {
	bullets.clear();
	beams.clear();
}