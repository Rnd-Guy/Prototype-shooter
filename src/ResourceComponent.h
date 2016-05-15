#pragma once
#include "SFMLIncludes.h"
#include <map>
#include <string>

class ResourceComponent {
	// Most entities will have their own resource component, which will store the textures
	//   for them.
	// Textures will be kept in an std::map

public:
	void initialise(std::string name);
	sf::Texture* getTexture(std::string tex);
	


private:
	void load(std::string key, std::string location);
	std::map<std::string, sf::Texture> resource;
	bool initialised;

};