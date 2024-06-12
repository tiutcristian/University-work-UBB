#pragma once
#include "Sensor.h"

class TemperatureSensor : public Sensor
{
private:
	double diameter;

public:
	TemperatureSensor(std::string producer, std::vector<double> recordings, double diameter) : Sensor(producer, recordings), diameter(diameter) {};
	~TemperatureSensor() {};
	bool sendAlert() override;
	double getPrice() override;
	std::string toString() override;
};

