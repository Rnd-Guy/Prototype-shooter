#include "Beam.h"
#include "Player.h"

ResourceComponent Beam::resourceComponent; // initialise() function called in PlayState constructor

Beam::Beam(sf::RenderWindow* window, std::string playerOrBoss, double damage, std::string type, double spawnX, double spawnY, double chargeTime, double duration, double param1, double param2, double param3, double param4, double param5, std::string presetBehaviour, Player* player) 
{
	this->window = window;
	x = spawnX;
	y = spawnY;
	width = 7;
	hitboxRadius = 2;
	hitboxDistance = 5;

	this->damage = damage;
	chargeTimer = chargeTime;
	beamDuration = duration;

	showHitbox = true; 

	active = false;
	hit = false;
	deleteFlag = false;
	behaviour = presetBehaviour;
	this->player = player;



	if (playerOrBoss == "player" || playerOrBoss == "Player" || playerOrBoss == "P" || playerOrBoss == "p") {
		damagePlayer = false;
		damageBoss = true;
	}
	else {
		damagePlayer = true;
		damageBoss = false;
		
	}
	initialise();
	calculatePath(type, param1, param2, param3, param4, param5);


}


void Beam::initialise() {
	beamSprite.setTexture(*(resourceComponent.getTexture("beamCharging")));
	beamSprite.setOrigin(3, 0);
	beamEndSprite.setTexture(*(resourceComponent.getTexture("beamEnd")));
	beamEndSprite.setOrigin(5, 0);

}


void Beam::calculatePath(std::string type, double param1, double param2, double param3, double param4, double param5) {
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
			hitboxXDistance = hitboxDistance * sin(quad1);
			hitboxYDistance = -1 * (hitboxDistance * cos(quad1));
		}
		else if (direction + directionOffset <= 180) {
			hitboxXDistance = hitboxDistance * cos(quad2);
			hitboxYDistance = hitboxDistance * sin(quad2);
		}
		else if (direction + directionOffset <= 270) {
			hitboxXDistance = -1 *  (hitboxDistance * sin(quad3));
			hitboxYDistance = hitboxDistance * cos(quad3);
		}
		else if (direction + directionOffset <= 360) {
			hitboxXDistance = -1 *  (hitboxDistance * cos(quad4));
			hitboxYDistance = -1 *  (hitboxDistance * sin(quad4));
		}
		else { // error checking
			//std::cout << "direction out of range" << std::endl;
		}
		
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
		return calculatePath("direction", direction, directionOffset);
	}

	generateHitboxes();
}

void Beam::generateHitboxes() {
	hitboxes.clear();
	hitboxPoints.clear();
	hitboxSprites.clear();

	double currentX = x - hitboxXDistance;
	double currentY = y - hitboxYDistance;

	while (currentX > 0 && currentX < 600 && currentY > 0 && currentY < 600) {
		hitboxPoints.push_back({ currentX, currentY });
		hitboxes.push_back(sf::FloatRect(currentX - hitboxRadius, currentY - hitboxRadius, (2 * hitboxRadius) + 1, (2 * hitboxRadius) + 1));
		if (showHitbox) {
			hitboxSprites.push_back(sf::Sprite());
			hitboxSprites.back().setTexture(*(resourceComponent.getTexture("beamHitbox")));
			hitboxSprites.back().setOrigin(2, 2);
			hitboxSprites.back().setPosition(sf::Vector2f(hitboxPoints.back()[0], hitboxPoints.back()[1]));
		}

		currentX += hitboxXDistance;
		currentY += hitboxYDistance;

	}
}

void Beam::update() {
	if (active == false) {
		if (chargeTimer <= 0) {
			active = true;
			beamSprite.setTexture(*(resourceComponent.getTexture("beam")));
		}
		else {
			--chargeTimer;
		}
	}

	//changeDirection(direction+1);
	updateBehaviour(behaviour);

	beamSprite.setPosition(hitboxPoints[0][0], hitboxPoints[0][1]);
	beamSprite.setRotation(direction - 180); // beam starts pointing down
	beamEndSprite.setRotation(direction - 180);

	--beamDuration;
	if (beamDuration < 0) deleteFlag = true;

}

void Beam::render() {
	if (hit) {
		window->draw(beamEndSprite);
		beamSprite.setTextureRect(sf::IntRect(0, 0, 7, beamLength));
	}
	else {
		beamSprite.setTextureRect(sf::IntRect(0, 0, 7, 600));
	}
	window->draw(beamSprite);
	if (showHitbox) {
		for (int i = 0; i < hitboxSprites.size(); ++i) {
			window->draw(hitboxSprites[i]);
		}
	}
	
}

bool Beam::checkCollision(sf::FloatRect otherHitbox) {
	if (active) {
		for (auto i = 0; i < hitboxes.size(); ++i) {
			if (otherHitbox.intersects(hitboxes[i])) {
				collision(i);
				return true;
			}
		}
	}
	// else
	hit = false;
	return false;
	
	
}

void Beam::changeDirection(double newDirection) {
	calculatePath("direction", newDirection);
}

void Beam::collision(int hitboxIndex) {
	hit = true;
	beamEndSprite.setPosition(hitboxPoints[hitboxIndex][0], hitboxPoints[hitboxIndex][1]);
	calculateLengthOfBeam(hitboxIndex);
}

void Beam::calculateLengthOfBeam(int hitboxIndex) {
	double startX = hitboxPoints[0][0];
	double startY = hitboxPoints[0][1];
	double endX = hitboxPoints[hitboxIndex][0];
	double endY = hitboxPoints[hitboxIndex][1];
	beamLength = pow(pow(endX - startX, 2) + pow(endY - startY, 2), 0.5);
}

void Beam::updateBehaviour(std::string presetBehaviour) {
	if (presetBehaviour == "") return;

	if (presetBehaviour == "follow") {
		// currently hardcoded, possibly generalise later
		x = player->getX();
		y = player->getY() - 10;
		calculatePath("direction", direction);
		// changeDirection(direction + 1);
	}


}