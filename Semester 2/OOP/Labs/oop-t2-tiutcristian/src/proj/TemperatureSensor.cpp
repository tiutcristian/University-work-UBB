#include "TemperatureSensor.h"
#include <sstream>

bool TemperatureSensor::sendAlert()
{
	int cnt = 0;
	for (auto& i : recordings)
	{
		if (i > 35)
			cnt++;
	}
	return cnt >= 2;
}

double TemperatureSensor::getPrice()
{
	if (diameter < 3)
		return 17;
	else
		return 9;
}

std::string TemperatureSensor::toString()
{
	std::string baseString = Sensor::toString();
	std::stringstream ss;
	ss << baseString << "Type: TemperatureSensor\n Recordings: ";
	for (auto& recording : recordings)
	{
		ss << recording << "mm ";
	}
	ss << "\n" << "Price: " << getPrice() << "\n";
	return ss.str();
}
