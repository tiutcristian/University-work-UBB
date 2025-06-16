#include "HumiditySensor.h"
#include <sstream>

bool HumiditySensor::sendAlert()
{
	int cnt = 0;
	for (auto& i : recordings)
	{
		if (i < 30)
			cnt++;
	}
	return cnt >= 2;
}

std::string HumiditySensor::toString()
{
	std::string baseString = Sensor::toString();
	std::stringstream ss;
	ss << baseString << "Type: HumiditySensor\n Recordings: ";
	for (auto& recording : recordings)
	{
		ss << recording << "% ";
	}
	ss << "\n" << "Price: " << getPrice() << "\n";
	return ss.str();
}
