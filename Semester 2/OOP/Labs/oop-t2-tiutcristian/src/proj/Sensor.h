#pragma once
#include <string>
#include <vector>

class Sensor
{
protected:
	std::string producer;
	std::vector<double> recordings;

public:
	Sensor(std::string producer, std::vector<double> recordings) : producer(producer), recordings(recordings) {}
	~Sensor() {}
	virtual bool sendAlert() = 0;
	virtual double getPrice() = 0;
	virtual std::string toString();
};

