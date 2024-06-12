#pragma once
#include <vector>
#include "Task.h"
#include <QAbstractListModel>
#include <QSortFilterProxyModel>

class Repo : public QAbstractListModel
{
private:
	std::vector<Task> tasks;
	void readFromFile();

public:
	Repo();

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

};