#include "Volunteer.h"

QString Volunteer::toString()
{
	QString res =  name + " | " + email + " | ";
	for (auto i : interests)
		res += i + ",";
	return res;
}

QString Volunteer::toStringComplete()
{
	QString res = name + " | " + email + " | ";
	for(int i = 0; i < interests.size(); i++)
		res += interests[i] + (i == interests.size() - 1 ? " | " : ",");
	res += department;
	return res;
}
