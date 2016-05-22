#include "RNG.h"

std::random_device RNG::rd;
std::mt19937 RNG::mt(RNG::rd());
std::uniform_int_distribution<> RNG::randomDirection(0,359);
std::uniform_int_distribution<> RNG::randomGameArea(11, 599);