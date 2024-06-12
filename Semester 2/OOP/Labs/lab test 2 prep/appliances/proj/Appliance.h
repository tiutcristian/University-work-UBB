#pragma once
#include <string>

class Appliance
{
protected:
	std::string id;

public:
	Appliance(std::string id) : id(id) {}
	virtual ~Appliance() {}

	virtual double consumedElectricity() = 0;
	virtual std::string toString();
	std::string getId() { return id; }	
};

