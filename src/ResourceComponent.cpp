#include "ResourceComponent.h"

// Although every state/player has their own resource component, all resource component things
//   will be done here to keep resource related things centralised

// Template for adding new resources:
//    load("key", "file location");

// the "name" key should be the same as the name of the class
void ResourceComponent::initialise(std::string name) {
	if (initialised == true) {
		return;
	}

	if (name == "MenuState") {
		load("background", "../res/Main Menu.png");
		load("selectionRectangle", "../res/Menu Selection.png");
	}

	if (name == "PlayState") {
		load("blackBackground", "../res/Black Background.png");
		load("orangeOverlay", "../res/Orange overlay.png");
	}

	if (name == "PausedState") {
		load("greyTint", "../res/Grey Tint.png");
		load("pauseMenu", "../res/Pause Menu.png");
		load("selectionRectangle", "../res/Pause Selection.png");

	}

	if (name == "Player") {
		load("playerSprite", "../res/Player.png");
		load("playerHitbox", "../res/Player Hitbox.png");
		load("powerBarBorder", "../res/Power Bar Border.png");
		load("bluePowerFill", "../res/Blue Power Bar Fill.png");
		load("redPowerFill", "../res/Red Power Bar Fill.png");
		load("yellowPowerFill", "../res/Yellow Power Bar Fill.png");
	}

	if (name == "Bullet") {
		load("whiteBullet", "../res/White Bullet.png");
	}

	if (name == "Boss") {
		load("blueRectangle", "../res/Boss Blue Rectangle.png");
		load("redRectangle", "../res/Boss Red Rectangle.png");
		load("yellowRectangle", "../res/Boss Yellow Rectangle.png");
		load("hpBorder", "../res/Boss HP Border.png");
		load("hpFill", "../res/Boss HP Fill.png");
	}

	if (name == "Beam") {
		load("beam", "../res/Beam.png");
		load("beamEnd", "../res/Beam End.png");
		load("beamCharging", "../res/Beam Charging.png");
		load("beamHitbox", "../res/Beam Hitbox.png");
	}

	initialised = true;
}

void ResourceComponent::load(std::string name, std::string location) {
	resource[name] = sf::Texture();
	resource[name].loadFromFile(location);
}


sf::Texture* ResourceComponent::getTexture(std::string tex) {
	return &(resource[tex]);
}