#include "Equation.h"

std::pair<QString, QString> Equation::getRoots()
{
	double d = getDiscriminant();
	if (d < 0)
	{
		return std::make_pair(
			QString::number(-b / (2 * a)) + "+" + QString::number(sqrt(-d) / (2 * a)) + "i",
			QString::number(-b / (2 * a)) + "-" + QString::number(sqrt(-d) / (2 * a)) + "i"
		);
	}
	else if (d == 0)
		return std::make_pair(
			QString::number(-b / (2 * a)), 
			QString::number(-b / (2 * a))
		);
	else
	{
		return std::make_pair(
			QString::number((-b + sqrt(d)) / (2 * a)),
			QString::number((-b - sqrt(d)) / (2 * a))
		);
	}
}

QString Equation::toString() const
{
	QString s;
	s += QString::number(a) + "*x^2";
	if (b < 0)
		s += QString::number(b) + "*x";
	else if (b > 0)
		s += "+" + QString::number(b) + "*x";
	if (c < 0)
		s += QString::number(c);
	else if (c > 0)
		s += "+" + QString::number(c);
	return s;
}
