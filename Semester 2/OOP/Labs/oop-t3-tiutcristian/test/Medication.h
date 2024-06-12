#pragma once
#include <QString>
class Medication
{
private:
	QString category;
	QString name;
	std::vector<QString> effects;

public:
	Medication(QString category, QString name, std::vector<QString> effects)
		: category{ category }, name{ name }, effects{ effects } {}

	QString getCategory() { return category; }
	QString getName() { return name; }
	std::vector <QString> getEffects() { return effects; }

	QString toString() { return category + " | " + name; }
};

