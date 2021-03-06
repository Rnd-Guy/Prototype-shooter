#include "Player.h"

Player::Player(sf::RenderWindow* window, std::vector<std::unique_ptr<Bullet> > &bulletVector, std::vector<std::unique_ptr<Beam> > &beamVector, FirePattern* firePattern) :
	bullets(bulletVector), beams(beamVector)
{
	this->window = window;
	this->firePattern = firePattern;
	resourceComponent.initialise("Player");

	// set textures
	playerSprite.setTexture(*(resourceComponent.getTexture("playerSprite")));
	playerHitbox.setTexture(*(resourceComponent.getTexture("playerHitbox")));
	redPowerBorder.setTexture(*(resourceComponent.getTexture("powerBarBorder")));
	bluePowerBorder.setTexture(*(resourceComponent.getTexture("powerBarBorder")));
	yellowPowerBorder.setTexture(*(resourceComponent.getTexture("powerBarBorder")));
	redPowerFill.setTexture(*(resourceComponent.getTexture("redPowerFill")));
	bluePowerFill.setTexture(*(resourceComponent.getTexture("bluePowerFill")));
	yellowPowerFill.setTexture(*(resourceComponent.getTexture("yellowPowerFill")));
	life1.setTexture(*(resourceComponent.getTexture("playerSprite")));
	life2.setTexture(*(resourceComponent.getTexture("playerSprite")));
	life3.setTexture(*(resourceComponent.getTexture("playerSprite")));
	life4.setTexture(*(resourceComponent.getTexture("playerSprite")));
	life5.setTexture(*(resourceComponent.getTexture("playerSprite")));
	life6.setTexture(*(resourceComponent.getTexture("playerSprite")));
	life7.setTexture(*(resourceComponent.getTexture("playerSprite")));
	life8.setTexture(*(resourceComponent.getTexture("playerSprite")));

	// set colour
	playerSprite.setColor(sf::Color::White);

	// set sprite positions for overlay elements
	redPowerBorder.setPosition(sf::Vector2f(645, 440));
	bluePowerBorder.setPosition(sf::Vector2f(685, 440));
	yellowPowerBorder.setPosition(sf::Vector2f(725, 440));
	redPowerFill.setPosition(sf::Vector2f(650,445));
	bluePowerFill.setPosition(sf::Vector2f(690, 445));
	yellowPowerFill.setPosition(sf::Vector2f(730, 445));
	life1.setPosition(sf::Vector2f(620, 240));
	life2.setPosition(sf::Vector2f(660, 240));
	life3.setPosition(sf::Vector2f(700, 240));
	life4.setPosition(sf::Vector2f(740, 240));
	life5.setPosition(sf::Vector2f(620, 270));
	life6.setPosition(sf::Vector2f(660, 270));
	life7.setPosition(sf::Vector2f(700, 270));
	life8.setPosition(sf::Vector2f(740, 270));

	// resize certain elements
	//life1.setScale(0.5, 0.5);
	//life2.setScale(0.5, 0.5);
	//life3.setScale(0.5, 0.5);
	//life4.setScale(0.5, 0.5);

	// set text
	font.loadFromFile("../res/Prototype.ttf");
	redLevelText.setFont(font);
	blueLevelText.setFont(font);
	yellowLevelText.setFont(font);
	livesText.setFont(font);

	redLevelText.setString("1");
	redLevelText.setColor(sf::Color::Red);
	redLevelText.setStyle(sf::Text::Bold);
	redLevelText.setCharacterSize(24);
	redLevelText.setPosition(sf::Vector2f(652, 410));
	blueLevelText.setString("1");
	blueLevelText.setColor(sf::Color::Blue);
	blueLevelText.setStyle(sf::Text::Bold);
	blueLevelText.setCharacterSize(24);
	blueLevelText.setPosition(sf::Vector2f(692, 410));
	yellowLevelText.setString("1");
	yellowLevelText.setColor(sf::Color::Yellow);
	yellowLevelText.setStyle(sf::Text::Bold);
	yellowLevelText.setCharacterSize(24);
	yellowLevelText.setPosition(sf::Vector2f(732, 410));
	livesText.setString("Lives:");
	livesText.setColor(sf::Color::White);
	livesText.setStyle(sf::Text::Bold);
	livesText.setCharacterSize(20);
	livesText.setPosition(610, 200);
	

	levelUpExp = { 0,100,400,2000,5000,999999999 };

	reset();
	playerSprite.setOrigin(10, 14);
	playerHitbox.setOrigin(5, 5);
	hitboxVisible = false;
	hitBoxRadius = 6;
	autofireOn = false;
}

void Player::reset() {
	x = 300;
	y = 550;
	previousX = 300;
	previousY = 550;
	speed = 2; // pixels per frame
	redExp = 0;
	blueExp = 0;
	yellowExp = 0;
	redLevel = 1; 
	blueLevel = 1;
	yellowLevel = 1;
	lives = 4;
	invincibilityTimer = 0;
	playerSprite.setColor(sf::Color::White);

	redTimer = 0;
	red5Timer = 0;
	blueTimer = 0;
	yellowTimer = 0;
	redLevelText.setString("1");
	blueLevelText.setString("1");
	yellowLevelText.setString("1");
}

void Player::moveUp() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) y -= speed/2;
	else y -= speed;
	if (y < 15) {
		y = 15; // top of the screen
	}
}

void Player::moveDown() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) y += speed/2;
	else y += speed;
	if (y > 585) {
		y = 585; // bottom of the screen
	}
}

void Player::moveLeft() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) x -= speed/2;
	else x -= speed;
	if (x < 15) {
		x = 15; // left of the screen
	}
}

void Player::moveRight() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) x += speed/2;
	else x += speed;
	if (x > 585) {
		x = 585; // right of the screen
	}
}

void Player::shift() {
	hitboxVisible = true;
}

void Player::update() {
	// exp update
	if (redExp > levelUpExp[redLevel]) {
		redExp -= levelUpExp[redLevel];
		++redLevel;
		redLevelText.setString(std::to_string(redLevel));
	}
	if (blueExp > levelUpExp[blueLevel]) {
		blueExp -= levelUpExp[blueLevel];
		++blueLevel;
		blueLevelText.setString(std::to_string(blueLevel));
	}
	if (yellowExp > levelUpExp[yellowLevel]) {
		yellowExp -= levelUpExp[yellowLevel];
		++yellowLevel;
		yellowLevelText.setString(std::to_string(yellowLevel));
	}

	// sprite update
	playerSprite.setPosition(sf::Vector2f(x, y));
	playerHitbox.setPosition(sf::Vector2f(x, y));
	// power bars
	redPowerFill.setPosition(sf::Vector2f(650,566-(120*(redExp/levelUpExp[redLevel]))));
	redPowerFill.setTextureRect(sf::IntRect(0, 0, 20, (120 * (redExp / levelUpExp[redLevel]))));
	bluePowerFill.setPosition(sf::Vector2f(690, 566 - (120 * (blueExp / levelUpExp[blueLevel]))));
	bluePowerFill.setTextureRect(sf::IntRect(0, 0, 20, (120 * (blueExp / levelUpExp[blueLevel]))));
	yellowPowerFill.setPosition(sf::Vector2f(730, 566 - (120 * (yellowExp / levelUpExp[yellowLevel]))));
	yellowPowerFill.setTextureRect(sf::IntRect(0, 0, 20, (120 * (yellowExp / levelUpExp[yellowLevel]))));

	// invincibility timer countdown
	if (invincibilityTimer > 0) {
		--invincibilityTimer;
		if (invincibilityTimer == 0) {
			playerSprite.setColor(sf::Color::White);
		}
	}

	// shoot update
	if (redTimer > 0) --redTimer;
	if (red5Timer > 0) --red5Timer;
	if (blueTimer > 0) --blueTimer;
	if (yellowTimer > 0) --yellowTimer;

	
	rectHitbox = sf::FloatRect(x - hitBoxRadius, y - hitBoxRadius, (2 * hitBoxRadius) + 1, (2 * hitBoxRadius) + 1);
}

void Player::renderGame() {
	window->draw(playerSprite);
	if (hitboxVisible) {
		window->draw(playerHitbox);
		hitboxVisible = false;
	}
	
}

void Player::renderOverlay() {
	window->draw(redPowerFill);
	window->draw(bluePowerFill);
	window->draw(yellowPowerFill);
	window->draw(redPowerBorder);
	window->draw(bluePowerBorder);
	window->draw(yellowPowerBorder);

	window->draw(redLevelText);
	window->draw(blueLevelText);
	window->draw(yellowLevelText);
	window->draw(livesText);

	if (lives >= 1)	window->draw(life1);
	if (lives >= 2) window->draw(life2);
	if (lives >= 3) window->draw(life3);
	if (lives >= 4) window->draw(life4);
	if (lives >= 5)	window->draw(life5);
	if (lives >= 6) window->draw(life6);
	if (lives >= 7) window->draw(life7);
	if (lives >= 8) window->draw(life8);
}


double Player::getX() {
	return x;
}

double Player::getY() {
	return y;
}

double Player::getHitBoxRadius() {
	return hitBoxRadius;
}

sf::FloatRect Player::getRectHitbox() {
	return rectHitbox;
}

void Player::shoot() {
	// bullet constructor: 
	// sf::RenderWindow * window, std::string type, 
	// double spawnX, double spawnY, double spawnSpeed, 
	// double param1, double param2, double param3, double param4
	redShoot();
	blueShoot();
	yellowShoot();
	
}

void Player::damaged(double damageOfBullet) {
	if (invincibilityTimer == 0) {
		--lives;
		invincibilityTimer = 120;
		playerSprite.setColor(sf::Color(255,255,255,50)); // set to very transparent
	}
}

void Player::damageBlue(double damageOfBullet) {
	blueExp += damageOfBullet;
}

void Player::damageRed(double damageOfBullet) {
	redExp += damageOfBullet;
}

void Player::damageYellow(double damageOfBullet) {
	yellowExp += damageOfBullet;
}

// shot types

void Player::redShoot() {
	if (redTimer == 0) {
		if (redLevel == 1 || redLevel >= 3) {
			//bullets.push_back(std::make_unique<Bullet>(window, "player", 5, "dir", x, y - 10, 5, 0));
			fire("bullet", 5, "dir", x, y - 10, 5, 0);
		}
		if (redLevel >= 2) {
			//bullets.push_back(std::make_unique<Bullet>(window, "player", 5, "dir", x - 5, y - 6, 5, 0));
			//bullets.push_back(std::make_unique<Bullet>(window, "player", 5, "dir", x + 5, y - 6, 5, 0));
			fire("bullet", 5, "dir", x - 5, y - 6, 5, 0);
			fire("bullet", 5, "dir", x + 5, y - 6, 5, 0);
		}
		if (redLevel >= 3) {
			//bullets.push_back(std::make_unique<Bullet>(window, "player", 5, "dir", x, y - 10, 5, 30));
			//bullets.push_back(std::make_unique<Bullet>(window, "player", 5, "dir", x, y - 10, 5, -30));
			fire("bullet", 5, "dir", x, y - 10, 5, 30);
			fire("bullet", 5, "dir", x, y - 10, 5, -30);
		}
		if (redLevel >= 4) {
			//bullets.push_back(std::make_unique<Bullet>(window, "player", 5, "dir", x - 10, y, 5, 0));
			//bullets.push_back(std::make_unique<Bullet>(window, "player", 5, "dir", x + 10, y, 5, 0));
			//bullets.push_back(std::make_unique<Bullet>(window, "player", 5, "dir", x, y - 10, 5, 15));
			//bullets.push_back(std::make_unique<Bullet>(window, "player", 5, "dir", x, y - 10, 5, -15));

			fire("bullet", 5, "dir", x - 10, y, 5, 0);
			fire("bullet", 5, "dir", x + 10, y, 5, 0);
			fire("bullet", 5, "dir", x, y - 10, 5, 15);
			fire("bullet", 5, "dir", x, y - 10, 5, -15);


		}
		

		redTimer = 10;
	}
	if (red5Timer == 0) {
		if (redLevel == 5) {
			firePattern->add("playerCircle", this);
		}
		red5Timer = 30;
	}

}

void Player::blueShoot() {
	// something boring for now: extra lives
	// these static variables are only initialised once
	static bool blueLevel2 = false;
	static bool blueLevel3 = false;
	static bool blueLevel4 = false;
	static bool blueLevel5 = false;
	if (blueLevel2 == false && blueLevel >= 2) {
		++lives;
		blueLevel2 = true;
	}
	if (blueLevel3 == false && blueLevel >= 3) {
		++lives;
		blueLevel3 = true;
	}
	if (blueLevel4 == false && blueLevel >= 4) {
		++lives;
		blueLevel4 = true;
	}
	if (blueLevel5 == false && blueLevel >= 5) {
		++lives;
		blueLevel5 = true;
	}
}

void Player::yellowShoot() {
	if (yellowTimer == 0) {
		if (yellowLevel == 2 || yellowLevel >= 4) {
			//beams.push_back(std::make_unique<Beam>(window, "player", 1, "dir", x, y, 0, 30, 0, 0, 0, 0, 0, "follow", this));
			fire("beam", 1, "dir", x, y - 10, 30, 0, 0, 0, 0, 0, "follow");


		}
		if (yellowLevel == 3) {
			fire("beam", 1, "dir", x - 5, y-5, 30, 0, 0,0, 0, 0, "follow");
			fire("beam", 1, "dir", x + 5, y-5, 30, 0, 0,0, 0, 0, "follow");
		}
		if (yellowLevel >= 4) {
			fire("beam", 1, "dir", x - 10, y - 5, 30, 0, 0, 0, 0, 0, "follow");
			fire("beam", 1, "dir", x + 10, y - 5, 30, 0, 0, 0, 0, 0, "follow");
		}

		if (yellowLevel == 5) {
			static bool beamLevel5 = false; // will only be initialised once
			if (beamLevel5 == false) { // will only be true once
				fire("beam", 3, "dir", "center", 999999, 0, 0, 0, 0, 0, "followClockwise");
				fire("beam", 3, "dir", "center", 999999, 60, 0, 0, 0, 0, "followClockwise");
				fire("beam", 3, "dir", "center", 999999, 120, 0, 0, 0, 0, "followClockwise");
				fire("beam", 3, "dir", "center", 999999, 180, 0, 0, 0, 0, "followClockwise");
				fire("beam", 3, "dir", "center", 999999, 240, 0, 0, 0, 0, "followClockwise");
				fire("beam", 3, "dir", "center", 999999, 300, 0, 0, 0, 0, "followClockwise");
				beamLevel5 = true;
			}
		}



		yellowTimer = 30;

	}


}

void Player::autofire() {
	if (autofireOn) autofireOn = false;
	else autofireOn = true;
}

bool Player::getAutofire() {
	return autofireOn;
}

void Player::fire(std::string className, double damage, std::string type, double spawnX, double spawnY, double speedDuration, double param1, double param2, double param3, double param4, double param5, std::string preset) {
	if (className == "bullet") {
		bullets.push_back(std::make_unique<Bullet>(window, "player", damage, type, spawnX, spawnY, speedDuration, param1, param2, param3, param4, param5));
	}
	if (className == "beam") {
		beams.push_back(std::make_unique<Beam>(window, "player", damage, type, spawnX, spawnY, 0, speedDuration, param1, param2, param3, param4, param5, preset, this));
	}
}

void Player::fire(std::string className, double damage, std::string type, std::string spawn, double speedDuration, double param1, double param2, double param3, double param4, double param5, std::string preset) {
	double spawnX = 0;
	double spawnY = 0;
	if (spawn == "top") {
		spawnX = x;
		spawnY = y - 10;
	}
	if (spawn == "left") {
		spawnX = x - 10;
		spawnY = y;
	}
	if (spawn == "right") {
		spawnX = x + 10;
		spawnY = y;
	}
	if (spawn == "center" || spawn == "centre") {
		spawnX = x;
		spawnY = y;
	}
		
	if (className == "bullet") {
		bullets.push_back(std::make_unique<Bullet>(window, "player", damage, type, spawnX, spawnY, speedDuration, param1, param2, param3, param4, param5));
	}
	if (className == "beam") {
		beams.push_back(std::make_unique<Beam>(window, "player", damage, type, spawnX, spawnY, 0, speedDuration, param1, param2, param3, param4, param5, preset, this));
	}
}

double Player::getPreviousX() {
	return previousX;
}

double Player::getPreviousY() {
	return previousY;
}

void Player::storePreviousPosition() {
	previousX = x;
	previousY = y;
}

//void Player::render(std::string gameOrOverlay) {
//	if (gameOrOverlay == "Game" || gameOrOverlay == "game" || gameOrOverlay == "") {
//		renderGame();
//	}
//	if (gameOrOverlay == "Overlay" || gameOrOverlay == "overlay") {
//		renderOverlay();
//	}
//}

void Player::render() {
	return;
}

void Player::debug() {
	return;
}

int Player::getLives() {
	return lives;
}