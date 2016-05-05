#include "Boss.h"
#include "Player.h" // required to use player.getX() and player.getY()


Boss::Boss(sf::RenderWindow* window, std::vector<std::unique_ptr<Bullet> > &bulletVector, std::vector<std::unique_ptr<Beam> > &beamVector, Player* playerPointer) :
	bullets(bulletVector), player(playerPointer), beams(beamVector) ,mt(rd()), randomDirection(0,359)
{
	this->window = window;
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

	secondFormHP = 6666;

}

void Boss::reset() {
	x = 20;
	y = 50;
	maxHP = 10000;
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
	currentHP -= damageOfBullet;
}

void Boss::damageRed(double damageOfBullet) {
	currentHP -= damageOfBullet;
}

void Boss::damageYellow(double damageOfBullet) {
	currentHP -= damageOfBullet;
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

// bullet constructor:
//Bullet(sf::RenderWindow* window,
//	std::string playerOrBoss,
//	double damage,
//	std::string type, // "direction" or "target"
//	double spawnX,
//	double spawnY,
//	double spawnSpeed,
//	double param1,			// direction or targetX
//	double param2 = 0,		// directionOffset or targetY
//	double param3 = 0,		// 0 or targetXOffset
//	double param4 = 0);		// 0 or targetYOffset


void Boss::redShoot() {
	// left red rectangle spawns bullets at 100,270
	// right red rectangle spawns bullets at 500,270
	if (currentHP > secondFormHP) {
		if (redTimer % 20 == 0) {
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "direction", 100, 270, 5, randomDirection(mt)));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "direction", 500, 270, 5, randomDirection(mt)));
			bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY()));
			bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 30));
			bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, -30));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, 100, 400, 0, 0, blueTimer));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY()));


			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 45));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 90));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 135));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 180));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 225));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 270));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY(), 0, 0, 315));
			bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY()));
			bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY(), 0, 0, 30));
			bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY(), 0, 0, -30));
		}

		if (redTimer % 30 == 0) {
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 100, 270, 5, player->getX(), player->getY()));
			//bullets.push_back(std::make_unique<Bullet>(window, "Boss", 1, "target", 500, 270, 5, player->getX(), player->getY()));
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
	if (yellowTimer % 300 == 0) {
		beams.push_back(std::make_unique<Beam>(window, "Boss", 1, "direction", 245, 330, 120, 600, 180));
		beams.push_back(std::make_unique<Beam>(window, "Boss", 1, "direction", 355, 330, 120, 600, 180));

	}

	if (yellowTimer % 90 == 0) {
		//beams.push_back(std::make_unique<Beam>(window, "Boss", 1, "target", 245, 330, 120, 180, player->getX(), player->getY()));
	}
	if (yellowTimer == 10) {
		//beams.push_back(std::make_unique<Beam>(window, "Boss", 1, "direction", 245, 330, 0, 999999, 180));
	}



	++yellowTimer;
}