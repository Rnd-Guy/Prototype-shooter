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
		load("background", "Resources/Main Menu.png");
		load("selectionRectangle", "Resources/Menu Selection.png");
	}

	if (name == "PlayState") {
		load("blackBackground", "Resources/Black Background.png");
		load("orangeOverlay", "Resources/Orange overlay.png");
	}

	if (name == "PausedState") {
		load("greyTint", "Resources/Grey Tint.png");
		load("pauseMenu", "Resources/Pause Menu.png");
		load("selectionRectangle", "Resources/Pause Selection.png");

	}

	if (name == "Player") {
		load("playerSprite", "Resources/Player.png");
		load("playerHitbox", "Resources/Player Hitbox.png");
		load("powerBarBorder", "Resources/Power Bar Border.png");
		load("bluePowerFill", "Resources/Blue Power Bar Fill.png");
		load("redPowerFill", "Resources/Red Power Bar Fill.png");
		load("yellowPowerFill", "Resources/Yellow Power Bar Fill.png");
	}

	if (name == "Bullet") {
		load("whiteBullet", "Resources/White Bullet.png");
	}

	if (name == "Boss") {
		load("blueRectangle", "Resources/Boss Blue Rectangle.png");
		load("redRectangle", "Resources/Boss Red Rectangle.png");
		load("yellowRectangle", "Resources/Boss Yellow Rectangle.png");
		load("hpBorder", "Resources/Boss HP Border.png");
		load("hpFill", "Resources/Boss HP Fill.png");
	}

	if (name == "Beam") {
		load("beam", "Resources/Beam.png");
		load("beamEnd", "Resources/Beam End.png");
		load("beamCharging", "Resources/Beam Charging.png");
		load("beamHitbox", "Resources/Beam Hitbox.png");
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