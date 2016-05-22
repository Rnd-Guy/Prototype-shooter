#pragma once

/* Mostly so I can have a pointer that can point to either the player or the boss
 * Also helps for when I have more entities 
*/

class GameObject {
public:
	virtual ~GameObject() = 0;

	virtual void update() = 0;
	virtual void render() = 0;
	virtual double getX() = 0;
	virtual double getY() = 0;

};