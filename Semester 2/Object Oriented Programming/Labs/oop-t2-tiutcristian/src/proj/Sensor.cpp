#include "Sensor.h"
#include <sstream>

std::string Sensor::toString()
{
	std::stringstream ss;
	ss << "Producer: " << producer << "\n";
	return ss.str();
}
