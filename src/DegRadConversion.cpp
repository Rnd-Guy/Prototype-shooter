#include "DegRadConversion.h"


double Convert::degToRad(double deg) {
	return (deg / 360)*(2 * pi);
}

double Convert::radToDeg(double rad) {
	return (rad / (2 * pi)) * 360;
}