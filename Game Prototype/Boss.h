#pragma once

#include <random> // for random shots
#include <memory> // for smart pointers
#include "Bullet.h"
#include "ResourceComponent.h"
#include "Beam.h"

class Player; // needs to know player to be able to shoot directed bullets aimed at player

class Boss {
public:
	Boss(sf::RenderWindow* window, std::vector<std::unique_ptr<Bullet> > &bulletVector, std::vector<std::unique_ptr<Beam> > &beamVector, Player* playerPointer);

	void update();
	void render();
	void reset();

	void damageRed(double damageOfBullet);
	void damageBlue(double damageOfBullet);
	void damageYellow(double damageOfBullet);

	sf::FloatRect getRedLeftHitBox();
	sf::FloatRect getRedRightHitBox();
	sf::FloatRect getYellowLeftHitBox();
	sf::FloatRect getYellowRightHitBox();
	sf::FloatRect getBlueHitBox();

	void redShoot();
	void blueShoot();
	void yellowShoot();

private:
	Player* player;

	double x;
	double y;
	double currentHP;
	double maxHP;
	double secondFormHP; // hp threshold before boss switches into second form

	// timers
	int redTimer;
	int blueTimer;
	int yellowTimer;

	// positioning the rectangles 
	double redLeftXOffset;
	double redLeftYOffset;
	double redRightXOffset;
	double redRightYOffset;
	double yellowLeftXOffset;
	double yellowLeftYOffset;
	double yellowRightXOffset;
	double yellowRightYOffset;
	double blueXOffset;
	double blueYOffset;

	sf::RenderWindow* window;
	std::vector <std::unique_ptr<Bullet> > &bullets;
	std::vector <std::unique_ptr<Beam> > &beams;
	ResourceComponent resourceComponent;

	sf::Sprite blueRectangle;
	sf::Sprite redLeftRectangle;
	sf::Sprite redRightRectangle;
	sf::Sprite yellowLeftRectangle;
	sf::Sprite yellowRightRectangle;

	sf::FloatRect blueRectangleHitBox;
	sf::FloatRect redLeftRectangleHitBox;
	sf::FloatRect redRightRectangleHitBox;
	sf::FloatRect yellowLeftRectangleHitBox;
	sf::FloatRect yellowRightRectangleHitBox;


	sf::Sprite hpBorder;
	sf::Sprite hpFill;

	// random number generator
	std::random_device rd;
	std::mt19937 mt;
	std::uniform_int_distribution<> randomDirection;


};