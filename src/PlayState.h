#pragma once

#include "GameState.h"
#include "ResourceComponent.h"
#include "Player.h"
#include "Bullet.h"
#include "Boss.h"
#include "FirePattern.h"

class PlayState : public GameState {
public:
	PlayState(Game* gamePointer, sf::RenderWindow* window);
	virtual void handleInput() override;
	virtual void update() override;
	virtual void render() override;
	virtual void enter(std::string string = "") override;
	virtual std::string exit() override;
	virtual void changeGameState(Game::State newState);		
	virtual void terminate();

	void reset();

	//test functions
	Player* getPlayer();
	Boss* getBoss();
	std::vector<std::unique_ptr<Bullet> > &getBullets();
	std::vector<std::unique_ptr<Beam> > &getBeam();


private:
	Game* gamePointer; // used to change game state
	int menuSelection; // is it on play or quit? 0 for play, 1 for quit
	sf::RenderWindow* window; // to draw
	ResourceComponent resourceComponent;

	Player player;
	Boss boss;
	std::vector<std::unique_ptr<GameObject> > gameObjects; // may be used in future when i have more entities (blue power?)
	std::vector<std::unique_ptr<Bullet> > bullets; // this will be passed to the player and boss
	sf::Sprite blackBackground;
	sf::Sprite orangeOverlay;
	std::vector<std::unique_ptr<Beam> > beams; // this will be passed to the player and boss
	FirePattern firePattern;



};



