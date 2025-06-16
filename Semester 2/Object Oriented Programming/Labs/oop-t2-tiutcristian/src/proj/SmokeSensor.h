#pragma once
#include "Sensor.h"
class SmokeSensor : public Sensor
{
public:
	SmokeSensor(std::string producer, std::vector<double> recordings) : Sensor(producer, recordings) {}
	bool sendAlert() override;
	double getPrice() override { return 25; }
	std::string toString() override;
};

