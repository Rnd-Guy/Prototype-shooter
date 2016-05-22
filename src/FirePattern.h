#pragma once

#include "SFMLIncludes.h"
#include "Bullet.h"

// keep bullet patterns localised for easier reusability and creation

#include <memory>
#include "Bullet.h"
#include "Beam.h"
#include "DegRadConversion.h"
#include "RNG.h"

class GameObject;

class FirePattern {
public:
	FirePattern(sf::RenderWindow* window, std::vector<std::unique_ptr<Bullet> > &bulletVector, std::vector<std::unique_ptr<Beam> > &beamVector);

	void update();
	void add(std::string pattern, GameObject* objectPointer = nullptr); // this is called by other objects to add a firing pattern to the queue
	void reset();

	class FirePatternInfo { // Make a vector of firePatternInfo to keep track of all the patterns
	public:
		FirePatternInfo(sf::RenderWindow* window, std::vector<std::unique_ptr<Bullet> > &bulletVector, std::vector<std::unique_ptr<Beam> > &beamVector, std::string pattern, GameObject* objectPointer = nullptr); // constructor
		// fire mostly avoids the need to call make_unique for every bullet/beam
		void fire(std::string className, std::string playerOrBoss, double damage, std::string type, double spawnX, double spawnY, double durationOrSpeed, double param1, double param2 = 0, double param3 = 0, double param4 = 0, double param5 = 0, double chargeTime = 0, std::string preset = "");
		void fire(std::string className, std::string playerOrBoss, double damage, std::string type, std::string spawn, double durationOrSpeed, double param1, double param2 = 0, double param3 = 0, double param4 = 0, double param5 = 0, double chargeTime = 0, std::string preset = "");
		void update();
		bool finished();
	private:
		double x = 0;
		double y = 0; 
		double val1 = 0; // used if data is needed to be kept between update() calls
		double val2 = 0;
		std::string pattern;
		int counter;
		int finalCounter;
		bool deleteFlag;
		sf::RenderWindow* window; // needed to pass onto bullets and beams
		std::vector<std::unique_ptr<Bullet> > &bullets; // needed to add bullets
		std::vector<std::unique_ptr<Beam> > &beams; // needed to add beams
		GameObject* objectPointer;
	};

private:
	sf::RenderWindow* window; // needed to pass onto FirePatternInfo
	std::vector<std::unique_ptr<Bullet> > &bullets; // needed to pass onto FirePatternInfo
	std::vector<std::unique_ptr<Beam> > &beams; // needed to pass onto FirePatternInfo
	std::vector<std::unique_ptr<FirePatternInfo> > ongoingPatterns;


};