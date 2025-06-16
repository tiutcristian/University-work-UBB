#pragma once
#include <vector>
#include "Sensor.h"

class Device
{
private:
	std::vector<Sensor*> sensors;
public: 	
	Device() {};
	~Device() {};
	void addSensor(Sensor* sensor) { sensors.push_back(sensor); }
	std::vector<Sensor*> getAllSensors() { return sensors; }
	std::vector<Sensor*> getAlertingSensors();
	void writeToFile(std::string filename, double price = -1);
};

