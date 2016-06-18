#include "FirePattern.h"
#include "GameObject.h"

FirePattern::FirePattern(sf::RenderWindow* window, std::vector<std::unique_ptr<Bullet> > &bulletVector, std::vector<std::unique_ptr<Beam> > &beamVector) :
	bullets(bulletVector), beams(beamVector)
{
	this->window = window;
}

void FirePattern::reset() {
	ongoingPatterns.clear();
}

void FirePattern::update() {
	for (auto i = 0; i < ongoingPatterns.size(); ++i) {
		ongoingPatterns[i]->update();
	}
	int iter = 0;
	while (iter < ongoingPatterns.size()) {
		if (ongoingPatterns[iter]->finished()) {
			ongoingPatterns.erase(ongoingPatterns.begin() + iter);
		}
		else {
			++iter;
		}
	}
}

void FirePattern::add(std::string pattern, GameObject* objectPointer) {
	// add pattern into vector
	ongoingPatterns.push_back(std::make_unique<FirePatternInfo>(window, bullets, beams, pattern, objectPointer)); 
}

void FirePattern::FirePatternInfo::fire(std::string className, std::string playerOrBoss, double damage, std::string type, double spawnX, double spawnY, double durationOrSpeed, double param1, double param2, double param3, double param4, double param5, double chargeTime, std::string preset) {
	if (className == "bullet") {
		bullets.push_back(std::make_unique<Bullet>(window, playerOrBoss, damage, type, spawnX, spawnY, durationOrSpeed, param1, param2, param3, param4, param5));
	}
	else if (className == "beam") {
		beams.push_back(std::make_unique<Beam>(window, playerOrBoss, damage, type, spawnX, spawnY, chargeTime, durationOrSpeed, param1, param2, param3, param4, param5, preset));
	}
}

void FirePattern::FirePatternInfo::fire(std::string className, std::string playerOrBoss, double damage, std::string type, std::string spawn, double durationOrSpeed, double param1, double param2, double param3, double param4, double param5, double chargeTime, std::string preset) {
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
		bullets.push_back(std::make_unique<Bullet>(window, playerOrBoss, damage, type, spawnX, spawnY, durationOrSpeed, param1, param2, param3, param4, param5));
	}
	else if (className == "beam") {
		beams.push_back(std::make_unique<Beam>(window, playerOrBoss, damage, type, spawnX, spawnY, chargeTime, durationOrSpeed, param1, param2, param3, param4, param5, preset));
	}
}


bool FirePattern::FirePatternInfo::finished() {
	return deleteFlag;
}

FirePattern::FirePatternInfo::FirePatternInfo(sf::RenderWindow * window, std::vector<std::unique_ptr<Bullet>>& bulletVector, std::vector<std::unique_ptr<Beam>>& beamVector, std::string pattern, GameObject * objectPointer) :
	bullets(bulletVector), beams(beamVector)
{
	this->window = window;
	counter = 0;
	finalCounter = 0; // default value
	this->pattern = pattern;
	this->objectPointer = objectPointer;
	deleteFlag = false;
	x = 300; // if not defined, spawn in the middle of the screen to show it's an error
	y = 300; 





}

void FirePattern::FirePatternInfo::update() {
	// this is where all the patterns are found/created

	// playerSquare
	if (pattern == "playerSquare") {
		finalCounter = 0; // define finalCounter inside here for convenience
		x = objectPointer->getX();
		y = objectPointer->getY();
		if (counter == 0) {
			for (auto i = 0; i < 5; ++i) {
				fire("bullet", "player", 5, "dir", x - 10 + (5 * i), y - 10, 5, 0); // top of square
				fire("bullet", "player", 5, "dir", x - 10 + (5 * i), y + 10, 5, 0); // bottom of square
			}
			for (auto i = 0; i < 3; ++i) {
				fire("bullet", "player", 5, "dir", x - 10, y - 5 + (5 * i), 5, 0); // left of square
				fire("bullet", "player", 5, "dir", x + 10, y - 5 + (5 * i), 5, 0); // right of square
			}
		}
	}

	// playerTriangle
	if (pattern == "playerTriangle") {
		finalCounter = 0;
		x = objectPointer->getX();
		y = objectPointer->getY();
		if (counter == 0) {
			for (auto i = 0; i < 5; ++i) {
				for (auto j = 0; j <= i; ++j) {
					fire("bullet", "player", 5, "dir", x - (2.5*i) + (5*j), y - 10 + (5 * i), 5, 0);
				}
			}
		}
	}

	// playerCircle
	if (pattern == "playerCircle") {
		finalCounter = 0;
		x = objectPointer->getX();
		y = objectPointer->getY();
		if (counter == 0) {
			for (auto i = 0; i < 15; ++i) {
				fire("bullet", "player", 5, "dir", x + 10*(sin(Convert::degToRad((360 / 15)*i))), y + 10 * (cos(Convert::degToRad((360 / 15)*i))), 5, 0);
			}
		}
	}

	// bossWall
	if (pattern == "bossWall") {
		// a series of bullet walls with a hole, subsequent holes are near previous holes
		finalCounter = 300;
		if (counter == 0) val1 = RNG::randomGameArea(RNG::mt);
		for (int k = 0; k < 301; k+=60) {
			if (counter == k) {
				double hole;
				do {
					hole = RNG::randomGameArea(RNG::mt);
				} while (hole < val1 - 100 || hole > val1 + 100);
				val1 = hole;
				for (int i = 15; i < 595; i += 5) {
					if (i < hole - 25 || i > hole + 25) {
						fire("bullet", "boss", 1, "dir", i, 270, 1.5, 180);
					}
				}
			}
		}
	}

	// bossTripleSpam - shoots multiple triple shots aimed at the player (not very readable)
	if (pattern == "bossTripleSpam") {		
		// objectPointer points to the player
		finalCounter = 300;
		for (int i = 0; i < 301; i += 30) {
			if (counter == i) {
				fire("bullet", "boss", 1, "target", "redLeft", 5, objectPointer->getX(), objectPointer->getY());
				fire("bullet", "boss", 1, "target", "redLeft", 5, objectPointer->getX(), objectPointer->getY(), 0, 0, 30);
				fire("bullet", "boss", 1, "target", "redLeft", 5, objectPointer->getX(), objectPointer->getY(), 0, 0, -30);
				fire("bullet", "boss", 1, "target", "redRight", 5, objectPointer->getX(), objectPointer->getY());
				fire("bullet", "boss", 1, "target", "redRight", 5, objectPointer->getX(), objectPointer->getY(), 0, 0, 30);
				fire("bullet", "boss", 1, "target", "redRight", 5, objectPointer->getX(), objectPointer->getY(), 0, 0, -30);
			}
		}
	}

	//bossRandomSpam
	if (pattern == "bossRandomSpam") {
		finalCounter = 300;
		if (counter % 2 == 0) {
			fire("bullet", "boss", 1, "dir", "redLeft", 3, RNG::randomDirection(RNG::mt));
			fire("bullet", "boss", 1, "dir", "redRight", 3, RNG::randomDirection(RNG::mt));
		}
	}

	if (pattern == "bossSingleSpam") {
		// objectPointer points to the player
		finalCounter = 300;
		for (int i = 0; i < 301; i += 2) {
			if (counter == i) {
				fire("bullet", "boss", 1, "target", "redLeft", 5, objectPointer->getX(), objectPointer->getY());
				fire("bullet", "boss", 1, "target", "redRight", 5, objectPointer->getX(), objectPointer->getY());
			}
		}
	}




	if (counter >= finalCounter) deleteFlag = true;
	++counter;
}
