#pragma once
#include <QString>
#include <vector>

class Volunteer
{
private:
	QString name;
	QString email;
	std::vector<QString> interests;
	QString department;

public:
	Volunteer(QString name, QString email, std::vector<QString> interests, QString department = "-")
		: name(name), email(email), interests(interests), department(department) {}
	QString getName() const { return name; }
	QString getEmail() const { return email; }
	QString getDepartment() const { return department; }
	std::vector<QString> geInterests() const { return interests; }
	void setName(QString name) { this->name = name; }
	void setEmail(QString email) { this->email = email; }
	void setDepartment(QString department) { this->department = department; }
	QString toString();
	QString toStringComplete();
};

