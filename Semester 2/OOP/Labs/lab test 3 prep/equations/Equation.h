#pragma once
#include <cmath>
#include <utility>
#include <string>
#include <QString>

class Equation
{
private:
	double a, b, c;

public:
	Equation(double a, double b, double c)
		: a(a), b(b), c(c) {}

	double getA() { return a; }
	double getB() { return b; }
	double getC() { return c; }

	void setA(double a) { this->a = a; }
	void setB(double b)	{ this->b = b; }
	void setC(double c) { this->c = c; }

	double getDiscriminant() const { return b * b - 4 * a * c; } 
	std::pair<QString, QString> getRoots();
	QString toString() const;
};

