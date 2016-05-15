#pragma once

#include <cmath>
#include "SFMLIncludes.h"
#include "ResourceComponent.h"
#include "DegRadConversion.h"
// Direction is taken with 0 as Up, 90 as Right, 180 as Down and 270 as Left
// X is 0 on left
// Y is 0 at the top of the screen

class PlayState;

class Bullet {
public:
	//virtual ~Bullet() {};
	// two types of constructors: one using speed and direction, other using speed and target
	//   for direction, param1 = direction, param2 = directionOffset, param3 and param4 are not used
	//   for target, param1 = targetX, param2 = targetY, param3 = targetXOffset, param4 = targetYOffset

	// unfortunately cannot find a suitable overload with default parameters without overload ambiguity

	// note this class can be used for actual bullets, but it's mostly designed to be a base class to be inherited from
	Bullet(sf::RenderWindow* window,
		std::string playerOrBoss,
		double damage,
		std::string type, // "direction" or "target"
		double spawnX,        
		double spawnY,        
		double spawnSpeed,    
		double param1,        // direction or targetX
		double param2 = 0,	  // directionOffset or targetY
		double param3 = 0,    // 0 or targetXOffset
		double param4 = 0,    // 0 or targetYOffset
		double param5 = 0);	  // 0 or directionOffset

	void calculatePath(std::string type, double speed, 
		double param1, double param2=0,  
		double param3=0, double param4=0, double param5=0);
	
	virtual void initialise(); // subclass specific behaviour eg changing directions and setting textures
	virtual void update(); // movement
	void render(); // render
	void collision();

	double getX();
	double getY();
	sf::FloatRect getRectHitBox();
	double getRadius();

	double getDistanceFromPoint(double x, double y);
protected:
	sf::RenderWindow* window;
	sf::Sprite bulletSprite;
	double radius;
	double x;
	double y;
	double speed;
	double direction;
	double directionOffset;
	double xSpeed;
	double ySpeed;
	double targetX;
	double targetY;
	double targetXOffset;
	double targetYOffset;
	
	double damage;  // how much damage bullet does
	bool damagePlayer; // does it hurt the player?
	bool damageBoss;   // does it hurt the boss?

	bool deleteFlag; // when the bullet should be deleted this should be set to true

	sf::FloatRect rectHitBox;
	// share one resourceComponent between bullet
	static ResourceComponent resourceComponent; // initialised in Bullet.cpp
	
	friend PlayState; // only used to initialise resourceComponent for bullets at game start
};