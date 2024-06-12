#include "DishWasher.h"
#include <sstream>

std::string DishWasher::toString()
{
	std::string baseString = Appliance::toString();
	std::stringstream ss;
	ss << baseString << ", type: dishwasher, consumed energy for one hour: " << consumedEnergyForOneHour;
	return ss.str();
}
