#pragma once

#include <cmath>
#include "SFMLIncludes.h"
#include "ResourceComponent.h"
#include "DegRadConversion.h"

class PlayState;
class Player;

class Beam {
public:
	Beam(sf::RenderWindow* window,
		std::string playerOrBoss,
		double damage,
		std::string type,		//		"Direction"					"Target"
		double spawnX,
		double spawnY,
		double chargeTime,
		double duration,
		double param1,			//		direction					targetX
		double param2 = 0,		//		directionOffset				targetY
		double param3 = 0,		//		unused						targetXOffset
		double param4 = 0,		//		unused						targetYOffset
		double param5 = 0,		//		unused						directionOffset
		std::string presetBehaviour = "",	// used for preset behaviour, like "follow" or "rotateClockwise" or "wobble"
		Player* player = nullptr);		// currently used for preset "follow" for player, may generalise this later
		

	void calculatePath(std::string type, 
		double param1, double param2 = 0,
		double param3 = 0, double param4 = 0, double param5 = 0);

	void generateHitboxes();

	virtual void initialise();
	virtual void update();
	void updateBehaviour(std::string presetBehaviour); // stuff like rotating the beam
	void render();
	

	bool checkCollision(sf::FloatRect otherHitbox); // if no collision, returns -1, else returns the index of the hitbox that it collides with
	void collision(int hitboxIndex); // index of hitbox which collides with player/boss
	void calculateLengthOfBeam(int hitboxIndex); // if collided, shorten the beam to end at the collision

	void changeDirection(double newDirection);




private:
	sf::RenderWindow* window;
	sf::Sprite beamSprite;
	sf::Sprite beamEndSprite;

	double width;
	double x;
	double y;
	double direction;
	double directionOffset;
	double targetX;
	double targetY;
	double targetXOffset;
	double targetYOffset;
	double chargeTimer; // time before beam activates (boss only)
	bool active; // true if beam can damage boss/player, false if not (ie when charging)
	bool hit; // true if beam has hit something this frame
	double beamLength;
	double beamDuration;

	std::string behaviour;
	Player* player;

	bool showHitbox; // debug purposes

	double damage;  // how much damage bullet does
	bool damagePlayer; // does it hurt the player?
	bool damageBoss;   // does it hurt the boss?
	

	bool deleteFlag; // when the bullet should be deleted this should be set to true

	sf::FloatRect rectHitBox;

	std::vector<sf::FloatRect> hitboxes; // a collection of square hitboxes
	std::vector<std::vector<double>> hitboxPoints; // points scattered along the beam, centre of hitboxes
	int hitboxRadius; // if the center of the hitbox is (x,y) then the top left corner is (x-hitboxradius, y-hitboxradius) (default is 2)
	double hitboxDistance; // distance between each hitbox (default 5)
	double hitboxXDistance; // x distance between each hitbox
	double hitboxYDistance; // y distance between each hitbox
	std::vector<sf::Sprite> hitboxSprites;

	// share one resourceComponent between beams
	static ResourceComponent resourceComponent; // initialised in Beam.cpp

	friend PlayState; // only used to initialise resourceComponent for bullets at game start




};