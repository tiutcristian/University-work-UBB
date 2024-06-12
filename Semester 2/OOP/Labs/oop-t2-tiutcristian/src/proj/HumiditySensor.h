#pragma once
#include "Sensor.h"

class HumiditySensor : public Sensor
{
public:
	HumiditySensor(std::string producer, std::vector<double> recordings) : Sensor(producer, recordings) {};
	~HumiditySensor() {};
	bool sendAlert() override;
	double getPrice() override { return 4; };
	std::string toString() override;
};

