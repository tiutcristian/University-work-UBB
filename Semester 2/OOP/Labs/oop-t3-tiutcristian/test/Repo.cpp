#include "Repo.h"
#include <fstream>
#include <QStringList>

void Repo::loadFromFile()
{
	std::ifstream f("input.txt");
	std::string line;
	while(std::getline(f, line))
	{
		QString name;
		QString category;
		std::vector<QString> effects;
		QStringList list = QString::fromStdString(line).split("|");
		category = list[0].trimmed();
		name = list[1].trimmed();
		QStringList effectsList = list[2].split(",");
		for (auto effect : effectsList)
		{
			effects.push_back(effect.trimmed());
		}
		Medication m(category, name, effects);
		this->medications.push_back(m);
	}
	f.close();
}

void Repo::sortByCategory()
{
	sort(medications.begin(), medications.end(), [](Medication& m1, Medication& m2) { 
		return m1.getCategory() < m2.getCategory(); });
}

Repo::Repo()
{
	this->loadFromFile();
	this->sortByCategory();
}

std::vector<Medication> Repo::getMedications(QString str) const
{
	if (str == "")
		return this->medications;
	std::vector<Medication> result;
	for (auto m : this->medications)
	{
		if (m.toString().contains(str))
			result.push_back(m);
	}
	return result;
}

std::vector<QString> Repo::getEffectsByName(QString name)
{
	for (auto m : this->medications)
	{
		if (m.getName() == name)
			return m.getEffects();
	}
	throw std::exception("Medication not found");
}
