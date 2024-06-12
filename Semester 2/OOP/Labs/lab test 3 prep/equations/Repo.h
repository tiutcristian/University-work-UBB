#pragma once
#include <vector>
#include "Equation.h"
#include <QAbstractListModel>

class Repo : public QAbstractListModel
{
	Q_OBJECT
private:
	std::vector<Equation> equations;
	void readFromFile();

public:
	Repo() { readFromFile(); }

	int rowCount(const QModelIndex& parent = QModelIndex()) const override { return equations.size(); }
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void updateEquation(double a, double b, double c, int index);
	std::vector<Equation> getEquations() { return equations; }
};

