#include "Device.h"
#include <fstream>
#include <algorithm>

std::vector<Sensor*> Device::getAlertingSensors()
{
	std::vector<Sensor*> alertingSensors;
	for (Sensor* sensor : sensors)
	{
		if (sensor->sendAlert())
		{
			alertingSensors.push_back(sensor);
		}
	}
	return alertingSensors;
}

void Device::writeToFile(std::string filename, double price)
{
	std::ofstream file(filename);
	std::vector<std::string> sensorStrings;
	for (Sensor* sensor : sensors)
	{
		if (price == -1 || sensor->getPrice() < price)
		{
			sensorStrings.push_back(sensor->toString());
		}
	}
	sort(sensorStrings.begin(), sensorStrings.end());
	for (std::string sensorString : sensorStrings)
	{
		file << sensorString << std::endl;
	}
	file.close();
}
