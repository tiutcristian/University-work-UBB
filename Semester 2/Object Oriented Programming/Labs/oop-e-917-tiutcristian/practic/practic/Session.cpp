#include "Session.h"
#include <fstream>
#include <string>
#include <QString>
#include <QStringList>
#include <vector>

void Session::readFromFile()
{
	std::ifstream fin("volunteers.txt");
	std::string line;
	while (getline(fin, line))
	{
		QStringList tokens = QString::fromStdString(line).split("|");
		std::vector<QString> interests;
		for (auto i : tokens[2].split(","))
			interests.push_back(i.trimmed());
		volunteers.push_back(Volunteer(
			tokens[0].trimmed(), 
			tokens[1].trimmed(), 
			interests, 
			tokens[3].trimmed()
		));
	}
	fin.close();
}

double Session::getScore(Volunteer v, Department dep)
{
	std::vector<QString> interests = v.geInterests();
	QStringList desc = dep.getDesc().split(",");
	int len = desc.size();
	int count = 0;
	for (auto i : interests)
		for (auto d : desc)
			if (i == d.trimmed())
				count++;
	return (double)count / len;
}

void Session::addVolunteer(Volunteer v)
{
	volunteers.push_back(v);
	notify();
}

void Session::assign(QString name, QString dep)
{
	for(auto &v : volunteers)
		if (v.getName() == name)
		{
			v.setDepartment(dep);
			notify();
			return;
		}
}

std::vector<Volunteer> Session::getTop3(Department dep)
{
	std::vector<Volunteer> v;
	for (auto vol : volunteers)
		if (vol.getDepartment() == "-")
			v.push_back(vol);
	sort(v.begin(), v.end(), [&](Volunteer a, Volunteer b) {
		return getScore(a, dep) > getScore(b, dep);
	});
	std::vector<Volunteer> res;
	for (int i = 0; i < 3 && i < v.size(); i++)
		res.push_back(v[i]);
	return res;
}

void Session::writeToFile()
{
	std::ofstream fout("volunteers.txt");
	for (auto v : volunteers)
		fout << v.toStringComplete().toStdString() << "\n";
}
