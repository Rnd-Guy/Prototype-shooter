#pragma once

#include <memory>
#include "Bullet.h"
#include "ResourceComponent.h"
#include "Beam.h"


class Player {
public:
	Player(sf::RenderWindow* window, std::vector<std::unique_ptr<Bullet> > &bulletVector, std::vector<std::unique_ptr<Beam> > &beamVector);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void shift();

	void shoot();
	void redShoot();
	void blueShoot();
	void yellowShoot();


	void update();
	void renderGame();    // game elements like the player sprite
	void renderOverlay();  // overlay elements like power bars
	void reset();

	double getX();
	double getY();
	double getHitBoxRadius();
	sf::FloatRect getRectHitbox();

	void damaged(double damageOfBullet);   // takes a bullet D:
	void damageBlue(double damageOfBullet); // damages boss blue
	void damageRed(double damageOfBullet);
	void damageYellow(double damageOfBullet);
private:
	double x;
	double y;
	double hitBoxRadius;
	double speed;
	bool hitboxVisible;
	sf::Sprite playerSprite;
	sf::Sprite playerHitbox;
	sf::FloatRect rectHitbox; // sometimes used for easier hitbox calculations
	ResourceComponent resourceComponent;
	sf::RenderWindow* window;

	int lives;
	sf::Sprite life1;
	sf::Sprite life2;
	sf::Sprite life3;
	sf::Sprite life4;
	int invincibilityTimer;

	sf::Sprite redPowerBorder;
	sf::Sprite bluePowerBorder;
	sf::Sprite yellowPowerBorder;
	sf::Sprite redPowerFill;
	sf::Sprite bluePowerFill;
	sf::Sprite yellowPowerFill;

	sf::Font font;
	sf::Text redLevelText;
	sf::Text blueLevelText;
	sf::Text yellowLevelText;
	sf::Text livesText;

	int redLevel;
	int yellowLevel;
	int blueLevel;
	double redExp;
	double yellowExp;
	double blueExp;
	double redTimer;
	double blueTimer;
	double yellowTimer;
	std::vector<int> levelUpExp; // levelUpExp[i] is the exp required to lvl from i to i+1


	std::vector<std::unique_ptr<Bullet> > &bullets;
	std::vector<std::unique_ptr<Beam> > &beams;
};