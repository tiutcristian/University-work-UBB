#pragma once
#include <iostream>
#include "Device.h"


class UI
{
private:
	Device& device;
public:
	UI(Device& device);
	~UI() {}
	void printMenu();
	void run();
	void addSensor();
	void printAllSensors();
	void printAlertingSensors();
	void saveToFile();
};

