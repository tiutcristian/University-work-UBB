#pragma once
#include <vector>
#include "Medication.h"

class Repo
{
private:
	std::vector<Medication> medications;

	void loadFromFile();
	void sortByCategory();

public:
	Repo();
	std::vector<Medication> getMedications(QString str = "") const;
	std::vector<QString> getEffectsByName(QString name);
};

