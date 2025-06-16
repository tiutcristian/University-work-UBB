#include "Repo.h"
#include <fstream>
#include <QFont>

void Repo::readFromFile()
{
	std::ifstream fin("eq.txt");
	char line[100];
	while (fin.getline(line, 100))
	{
		double a, b, c;
		sscanf(line, "%lf|%lf|%lf", &a, &b, &c);
		equations.push_back(Equation(a, b, c));
	}
}

QVariant Repo::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		return equations[index.row()].toString();
	}
	else if (role == Qt::FontRole)
	{
		QFont font("Times");
		if (equations[index.row()].getDiscriminant() >= 0)
			font.setBold(true);
		else
			font.setBold(false);
		return font;
	}
	return QVariant();
}

void Repo::updateEquation(double a, double b, double c, int index)
{
	equations[index].setA(a);
	equations[index].setB(b);
	equations[index].setC(c);
}
