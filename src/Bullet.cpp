#include "Bullet.h"
#include <iostream>

// direction is taken as 0 as up, 90 as right, 180 as down and 270 as left
// y values start from the top, x values start from the left

// initialise static member
ResourceComponent Bullet::resourceComponent; // initialise() function called in PlayState constructor

Bullet::Bullet(sf::RenderWindow * window, std::string playerOrBoss, double damage, std::string type, double spawnX, double spawnY, double spawnSpeed, double param1, double param2, double param3, double param4, double param5)
{
	this->window = window;
	x = spawnX;
	y = spawnY;
	radius = 3;
	initialise();
	calculatePath(type, spawnSpeed, param1, param2, param3, param4, param5);
	deleteFlag = false;
	this->damage = damage;
	if (playerOrBoss == "player" || playerOrBoss == "Player" || playerOrBoss == "P" || playerOrBoss == "p") {
		damagePlayer = false;
		damageBoss = true;
	}
	else {
		damagePlayer = true;
		damageBoss = false;
		bulletSprite.setColor(sf::Color::Red);
	}

}

void Bullet::initialise() {
	
	bulletSprite.setTexture(*(resourceComponent.getTexture("whiteBullet")));
	bulletSprite.setOrigin(2, 2);
}


void Bullet::calculatePath(std::string type, double speed, double param1, double param2, double param3, double param4, double param5)
{
	this->speed = speed;
	// direction
	if (type == "d" || type == "dir" || type == "direction") {
		direction = param1;
		directionOffset = param2;

		// get direction in range [0,360)
		while (direction + directionOffset >= 360) direction -= 360;
		while (direction + directionOffset < 0) direction += 360;

		// temporary variables for clarity
		double quad1 = Convert::degToRad(direction + directionOffset);
		double quad2 = Convert::degToRad(direction + directionOffset - 90);
		double quad3 = Convert::degToRad(direction + directionOffset - 180);
		double quad4 = Convert::degToRad(direction + directionOffset - 270);
		
		if (direction + directionOffset <= 90 && direction + directionOffset >= 0) {
			xSpeed = speed * sin(quad1);
			ySpeed = -1 * (speed * cos(quad1));
		}
		else if (direction + directionOffset <= 180) {
			xSpeed = speed * cos(quad2);
			ySpeed = speed * sin(quad2);
		}
		else if (direction + directionOffset <= 270) {
			xSpeed = -1 * (speed * sin(quad3));
			ySpeed = speed * cos(quad3);
		}
		else if (direction + directionOffset <= 360) {
			xSpeed = -1 * (speed * cos(quad4));
			ySpeed = -1 * (speed * sin(quad4));
		}
		else { // error checking
			std::cout << "direction out of range" << std::endl;
		}
		return;
	}
	// target (calculate direction, then call calculatePath again with direction instead))
	if (type == "t" || type == "tar" || type == "target") {
		targetX = param1;
		targetY = param2;
		targetXOffset = param3;
		targetYOffset = param4;
		directionOffset = param5;

		double deltaX = targetX + targetXOffset - x;
		double deltaY = targetY + targetYOffset - y;

		// deltaX is positive if the target is to the right of the bullet's current position
		// deltaY is positive if the target is below the bullet's current position

		if (deltaX == 0 && deltaY == 0) {
			direction = 0; // default
		}
		else if (deltaX == 0) {
			if (deltaY < 0) direction = 0;
			if (deltaY > 0) direction = 180;
		}
		else if (deltaY == 0) {
			if (deltaX < 0) direction = 270;
			if (deltaX > 0) direction = 90;
		}
		else if (deltaX > 0 && deltaY < 0) { // angle between 0 and 90
			direction = Convert::radToDeg(atan(deltaX / (-deltaY)));
		}
		else if (deltaX > 0 && deltaY > 0) { // angle between 90 and 180
			direction = 90 + Convert::radToDeg(atan(deltaY / deltaX));
		}
		else if (deltaX < 0 && deltaY > 0) { // angle between 180 and 270
			direction = 180 + Convert::radToDeg(atan((-deltaX) / deltaY));
		}
		else if (deltaX < 0 && deltaY < 0) { // angle between 270 and 360
			direction = 270 + Convert::radToDeg(atan((-deltaY) / (-deltaX)));
		}
		return calculatePath("direction", speed, direction, directionOffset);
	}
}





void Bullet::update() {
	x += xSpeed;
	y += ySpeed;

	bulletSprite.setPosition(sf::Vector2f(x, y));

	if (x < -10 || x > 610 || y < -10 || y > 610) {
		deleteFlag = true;
	}

	rectHitBox = bulletSprite.getGlobalBounds();
}

void Bullet::render() {
	window->draw(bulletSprite);
}

double Bullet::getX() {
	return x;
}

double Bullet::getY() {
	return y;
}

sf::FloatRect Bullet::getRectHitBox() {
	return rectHitBox;
}

void Bullet::collision() {
	deleteFlag = true;
}

double Bullet::getRadius() {
	return radius;
}

double Bullet::getDistanceFromPoint(double x, double y) {
	return pow(pow(this->x - x, 2) + pow(this->y - y, 2), 0.5);
}