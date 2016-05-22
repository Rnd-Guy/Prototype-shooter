#include "Boss.h"
#include "Player.h" // required to use player.getX() and player.getY()


Boss::Boss(sf::RenderWindow* window, std::vector<std::unique_ptr<Bullet> > &bulletVector, std::vector<std::unique_ptr<Beam> > &beamVector, Player* playerPointer, FirePattern* firePattern) :
	bullets(bulletVector), player(playerPointer), beams(beamVector) 
{
	this->window = window;
	this->firePattern = firePattern;
	reset();
	resourceComponent.initialise("Boss");
	blueRectangle.setTexture(*(resourceComponent.getTexture("blueRectangle")));
	redLeftRectangle.setTexture(*(resourceComponent.getTexture("redRectangle")));
	redRightRectangle.setTexture(*(resourceComponent.getTexture("redRectangle")));
	yellowLeftRectangle.setTexture(*(resourceComponent.getTexture("yellowRectangle")));
	yellowRightRectangle.setTexture(*(resourceComponent.getTexture("yellowRectangle")));
	hpBorder.setTexture(*(resourceComponent.getTexture("hpBorder")));
	hpFill.setTexture(*(resourceComponent.getTexture("hpFill")));

	hpBorder.setPosition(sf::Vector2f(20, 20));
	hpFill.setPosition(sf::Vector2f(22, 22));

	redTimer = 1;
	blueTimer = 1;
	yellowTimer = 1;

	secondFormHP = 13000;

}

void Boss::reset() {
	x = 20;
	y = 50;
	maxHP = 20000;
	currentHP = maxHP;
	// reset position
	redLeftXOffset = 0;
	redLeftYOffset = 50;
	redRightXOffset = 410;
	redRightYOffset = 50;
	yellowLeftXOffset = 200;
	yellowLeftYOffset = 180;
	yellowRightXOffset = 310;
	yellowRightYOffset = 180;
	blueXOffset = 130;
	blueYOffset = 0;
	redTimer = 1;
	blueTimer = 1;
	yellowTimer = 1;
}

void Boss::update() {
	// update sprites and update hitboxes
	blueRectangle.setPosition(sf::Vector2f(x + blueXOffset, y + blueYOffset));
	redLeftRectangle.setPosition(sf::Vector2f(x + redLeftXOffset, y + redLeftYOffset));
	redRightRectangle.setPosition(sf::Vector2f(x + redRightXOffset, y + redRightYOffset));
	yellowLeftRectangle.setPosition(sf::Vector2f(x + yellowLeftXOffset, y + yellowLeftYOffset));
	yellowRightRectangle.setPosition(sf::Vector2f(x + yellowRightXOffset, y + yellowRightYOffset));
	redLeftRectangleHitBox = redLeftRectangle.getGlobalBounds();
	redRightRectangleHitBox = redRightRectangle.getGlobalBounds();
	yellowLeftRectangleHitBox = yellowLeftRectangle.getGlobalBounds();
	yellowRightRectangleHitBox = yellowRightRectangle.getGlobalBounds();
	blueRectangleHitBox = blueRectangle.getGlobalBounds();

	if (currentHP >= 0) {
		hpFill.setTextureRect(sf::IntRect(0, 0, (currentHP / maxHP) * 556, 6));
	}
	else {
		hpFill.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}

	// shoot
	redShoot();
	blueShoot();
	yellowShoot();


}

void Boss::render() {
	window->draw(blueRectangle);
	window->draw(redLeftRectangle);
	window->draw(redRightRectangle);
	window->draw(yellowLeftRectangle);
	window->draw(yellowRightRectangle);
	window->draw(hpBorder);
	window->draw(hpFill);


}

// may put specific colour mechanics here
void Boss::damageBlue(double damageOfBullet) {
	double previousHP = currentHP;
	currentHP -= damageOfBullet;
	if (previousHP > secondFormHP && currentHP <= secondFormHP) {
		redTimer = 0;
		blueTimer = 0;
		yellowTimer = 0;
	}
}

void Boss::damageRed(double damageOfBullet) {
	double previousHP = currentHP;
	currentHP -= damageOfBullet;
	if (previousHP > secondFormHP && currentHP <= secondFormHP) {
		redTimer = 0;
		blueTimer = 0;
		yellowTimer = 0;
	}
}

void Boss::damageYellow(double damageOfBullet) {
	double previousHP = currentHP;
	currentHP -= damageOfBullet;
	if (previousHP > secondFormHP && currentHP <= secondFormHP) {
		redTimer = 0;
		blueTimer = 0;
		yellowTimer = 0;
	}
}

sf::FloatRect Boss::getBlueHitBox() {
	return blueRectangleHitBox;
}

sf::FloatRect Boss::getRedLeftHitBox() {
	return redLeftRectangleHitBox;
}

sf::FloatRect Boss::getRedRightHitBox() {
	return redRightRectangleHitBox;
}

sf::FloatRect Boss::getYellowLeftHitBox() {
	return yellowLeftRectangleHitBox;
}

sf::FloatRect Boss::getYellowRightHitBox() {
	return yellowRightRectangleHitBox;
}


void Boss::redShoot() {
	// left red rectangle spawns bullets at 100,270
	// right red rectangle spawns bullets at 500,270
	// fire constructor1: (className, type, x, y, durationOrSpeed, param1, param2, param3, param4, param5, chargeTime, preset);
	// fire constructor2: (className, type, spawn, durationOrSpeed, param1, param2, param3, param4, param5, chargeTime, preset);
	// set direction to randomDirection(mt) for a random direction
	if (currentHP > secondFormHP) { // phase 1
		if (redTimer % 15 == 0) {
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "direction", 100, 270, 5, randomDirection(mt)));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "direction", 500, 270, 5, randomDirection(mt)));
			fire("bullet", "dir", "redLeft", 5, RNG::randomDirection(RNG::mt));
			fire("bullet", "dir", "redRight", 5, RNG::randomDirection(RNG::mt));


			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY()));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 30));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, -30));

			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, 100, 400, 0, 0, blueTimer));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY()));


			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 45));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 90));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 135));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 180));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 225));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 270));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 315));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY()));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY(), 0, 0, 30));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY(), 0, 0, -30));
		}

		if (redTimer % 120 == 0) {
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY()));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY()));
			fire("bullet", "target", "redLeft", 5, player->getX(), player->getY());
		}
		if (redTimer % 120 == 60) {
			fire("bullet", "target", "redRight", 5, player->getX(), player->getY());
		}



	}
	else if (currentHP > 0) {
		if (redTimer % 10 == 0) {
			fire("bullet", "dir", "redLeft", 5, RNG::randomDirection(RNG::mt));
			fire("bullet", "dir", "redRight", 5, RNG::randomDirection(RNG::mt));
		}

		if (redTimer % 2000 == 0) {
			firePattern->add("bossWall");
		}
		if (redTimer % 2000 == 1000) {
			firePattern->add("bossTripleSpam", player);
		}
		if (redTimer % 2000 == 1400) {
			firePattern->add("bossSingleSpam", player);
		}
	}



	++redTimer;
}

void Boss::blueShoot() {
	++blueTimer;
}

void Boss::yellowShoot() {
	// left laser spawn = 245,330
	// right laser spawn = 355,330
	// beam constructor: (window, playerOrBoss, damage, type, x, y, chargeTime, duration, param1, param2, param3, param4, param5)
	// fire constructor1: (className, type, x, y, durationOrSpeed, param1, param2, param3, param4, param5, chargeTime, preset);
	// fire constructor2: (className, type, spawn, durationOrSpeed, param1, param2, param3, param4, param5, chargeTime, preset);
	if (currentHP > secondFormHP) {
		if (yellowTimer % 600 == 0) {
			fire("beam", "dir", "yellowLeft", 200, 135, 0, 0, 0, 0, 100);
			fire("beam", "dir", "yellowLeft", 200, 225, 0, 0, 0, 0, 100);
			fire("beam", "dir", "yellowRight", 200, 135, 0, 0, 0, 0, 100);
			fire("beam", "dir", "yellowRight", 200, 225, 0, 0, 0, 0, 100);
		}
		if (yellowTimer % 600 == 300) {
			//beams.push_back(std::make_unique<Beam>(window, "Boss", 1, "direction", 245, 330, 120, 240, 180));
			//beams.push_back(std::make_unique<Beam>(window, "Boss", 1, "direction", 355, 330, 120, 240, 180));

			fire("beam", "dir", "yellowLeft", 200, 180, 0, 0, 0, 0, 100);
			fire("beam", "dir", "yellowRight", 200, 180, 0, 0, 0, 0, 100);

		}

		if (yellowTimer % 90 == 0) {
			//beams.push_back(std::make_unique<Beam>(window, "Boss", 1, "target", 245, 330, 120, 180, player->getX(), player->getY()));
		}
		if (yellowTimer == 10) {
			//beams.push_back(std::make_unique<Beam>(window, "Boss", 1, "direction", 245, 330, 0, 999999, 180));
		}
	}
	else if (currentHP > 0) {
		if (yellowTimer % 2000 == 420) {
			fire("beam", "dir", "yellowLeft", 350, 90, 0, 0, 0, 0, 100, "slowClockwise");
			fire("beam", "dir", "yellowLeft", 350, 135, 0, 0, 0, 0, 100, "slowClockwise");
			fire("beam", "dir", "yellowLeft", 350, 180, 0, 0, 0, 0, 100, "slowClockwise");
			fire("beam", "dir", "yellowLeft", 350, 225, 0, 0, 0, 0, 100, "slowClockwise");

			fire("beam", "dir", "yellowRight", 350, 90, 0, 0, 0, 0, 100, "slowClockwise");
			fire("beam", "dir", "yellowRight", 350, 135, 0, 0, 0, 0, 100, "slowClockwise");
			fire("beam", "dir", "yellowRight", 350, 180, 0, 0, 0, 0, 100, "slowClockwise");
			fire("beam", "dir", "yellowRight", 350, 245, 0, 0, 0, 0, 100, "slowClockwise"); // changed to remove a part where you cannot avoid getting hurt
		}
		if (yellowTimer % 2000 == 670) {
			fire("beam", "dir", "yellowLeft", 350, 135, 0, 0, 0, 0, 100, "slowAntiClockwise");
			fire("beam", "dir", "yellowLeft", 350, 180, 0, 0, 0, 0, 100, "slowAntiClockwise");
			fire("beam", "dir", "yellowLeft", 350, 225, 0, 0, 0, 0, 100, "slowAntiClockwise");
			fire("beam", "dir", "yellowLeft", 350, 270, 0, 0, 0, 0, 100, "slowAntiClockwise");

			fire("beam", "dir", "yellowRight", 350, 135, 0, 0, 0, 0, 100, "slowAntiClockwise");
			fire("beam", "dir", "yellowRight", 350, 180, 0, 0, 0, 0, 100, "slowAntiClockwise");
			fire("beam", "dir", "yellowRight", 350, 225, 0, 0, 0, 0, 100, "slowAntiClockwise");
			fire("beam", "dir", "yellowRight", 350, 290, 0, 0, 0, 0, 100, "slowAntiClockwise"); // changed to remove a part where you cannot avoid getting hurt
		}
	}



	++yellowTimer;
}

void Boss::fire(std::string className, std::string type, double spawnX, double spawnY, double durationOrSpeed, double param1, double param2, double param3, double param4, double param5, double chargeTime, std::string preset) {
	if (className == "bullet") {
		bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, type, spawnX, spawnY, durationOrSpeed, param1, param2, param3, param4, param5));
	}
	else if (className == "beam") {
		beams.push_back(std::make_unique<Beam>(window, "Boss", 1, type, spawnX, spawnY, chargeTime, durationOrSpeed, param1, param2, param3, param4, param5, preset));
	}
}

void Boss::fire(std::string className, std::string type, std::string spawn, double durationOrSpeed, double param1, double param2, double param3, double param4, double param5, double chargeTime, std::string preset) {
	double spawnX;
	double spawnY;
	if (spawn == "redLeft" || spawn == "leftRed") {
		spawnX = 100;
		spawnY = 270;
	}
	else if (spawn == "redRight" || spawn == "rightRed") {
		spawnX = 500;
		spawnY = 270;
	}
	else if (spawn == "yellowLeft" || spawn == "leftYellow") {
		spawnX = 245;
		spawnY = 330;
	}
	else if (spawn == "yellowRight" || spawn == "rightYellow") {
		spawnX = 355;
		spawnY = 330;
	}

	if (className == "bullet") {
		bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, type, spawnX, spawnY, durationOrSpeed, param1, param2, param3, param4, param5));
	}
	else if (className == "beam") {
		beams.push_back(std::make_unique<Beam>(window, "Boss", 1, type, spawnX, spawnY, chargeTime, durationOrSpeed, param1, param2, param3, param4, param5, preset));
	}
}

double Boss::getX() {
	return 0;
}

double Boss::getY() {
	return 0;
}

void Boss::debug() {
	//currentHP = 6000;
	//redTimer = 0;
	//blueTimer = 0;
	//yellowTimer = 0;
	//return;
}