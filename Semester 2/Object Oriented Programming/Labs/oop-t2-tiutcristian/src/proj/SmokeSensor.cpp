#include "SmokeSensor.h"
#include <sstream>

bool SmokeSensor::sendAlert()
{
	int cnt = 0;
	for (auto& i : recordings)
	{
		if (i > 1600)
			return true;
	}
	return false;
}

std::string SmokeSensor::toString()
{
	std::string baseString = Sensor::toString();
	std::stringstream ss;
	ss << baseString << "Type: SmokeSensor\n Recordings: ";
	for (auto& recording : recordings)
	{
		ss << recording << " ";
	}
	ss << "\n" << "Price: " << getPrice() << "\n";
	return ss.str();
}
