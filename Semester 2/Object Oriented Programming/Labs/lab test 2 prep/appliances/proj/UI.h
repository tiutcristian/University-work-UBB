#pragma once
#include "Service.h"
#include <iostream>

class UI
{
private:
	Service& service;

public:
	UI(Service& service);

	void printMenu();
	void runUI();
	void addAppliance();
	void showAll();
	void showInefficient();
	void saveToFile();
};

