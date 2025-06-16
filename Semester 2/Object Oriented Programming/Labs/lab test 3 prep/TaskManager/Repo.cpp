#include "Repo.h"
#include <fstream>
#include <QStringList>
#include <QFont>
#include <algorithm>

void Repo::readFromFile()
{
	std::ifstream fin("tasks.txt");
	char line[100];
	while (fin.getline(line, 100))
	{
		QStringList tokens = QString(line).split("|");
		tasks.push_back(
			Task(
				tokens[0],
				tokens[1].trimmed().toInt(),
				tokens[2].trimmed().toInt()
			)
		);
	}
	fin.close();
	std::sort(tasks.begin(), tasks.end(), [](const Task& t1, const Task& t2) { 
		return (
			t1.getPriority() < t2.getPriority() ||
			(t1.getPriority() == t2.getPriority() && t1.getDuration() < t2.getDuration())
		); 
	});
}

Repo::Repo()
{
	readFromFile();
}

int Repo::rowCount(const QModelIndex& parent) const
{
	return tasks.size();
}

QVariant Repo::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		return tasks[index.row()].toString();
	}
	else if (role == Qt::FontRole)
	{
		QFont font("Helvetica");
		if (tasks[index.row()].getPriority() == 1)
		{
			font.setBold(true);
		}
		else
		{
			font.setBold(false);
		}
		return font;
	}
	return QVariant();
}