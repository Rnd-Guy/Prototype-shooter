#pragma once
#include "Bullet.h"

// the standard shot type for the player. Upgraded with red power levels

class BasicPlayerBullet : public Bullet {
	BasicPlayerBullet(sf::RenderWindow* window,
		// std::string playerOrBoss,
		// double damage,
		std::string type, // "direction" or "target"
		double spawnX,
		double spawnY,
		double spawnSpeed,
		double param1,
		double param2 = 0,
		double param3 = 0,
		double param4 = 0,
		double param5 = 0);









};