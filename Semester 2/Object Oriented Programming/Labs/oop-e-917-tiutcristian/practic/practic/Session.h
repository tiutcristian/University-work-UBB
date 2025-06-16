#pragma once
#include "Subject.h"
#include "Volunteer.h"
#include "Department.h"

class Session : public Subject
{
private:
	std::vector<Volunteer> volunteers;

	void readFromFile();

public:
	Session() { readFromFile(); }
	std::vector<Volunteer> getVolunteers() const { return volunteers; }
	void addVolunteer(Volunteer v);
	void assign(QString name, QString dep);
	std::vector<Volunteer> getTop3(Department dep);
	void writeToFile();
	double getScore(Volunteer v, Department dep);
};

