#pragma once
#include <random>
// global RNG for the game

namespace RNG {
	// other distributions may be created by classes which need them
	// direction is fairly standard however

	// how to use: call RNG::randomDirection(RNG::mt) to get a random direction
	extern std::random_device rd;
	extern std::mt19937 mt;
	extern std::uniform_int_distribution<> randomDirection;
	extern std::uniform_int_distribution<> randomGameArea; // 11-599
}