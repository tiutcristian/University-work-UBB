#include "Repo.h"
#include <fstream>
#include <QStringList>
#include <algorithm>

void Repo::loadFromFile()
{
	std::ifstream fin("docs.txt");
	char line[100];
	while (fin.getline(line, 100))
	{
		QStringList parts = QString(line).split("|");
		QString name = parts[0].trimmed();
		QStringList keys = parts[1].split(",");
		std::vector<QString> keywords;
		for (auto key : keys)
			keywords.push_back(key.trimmed());
		QString content = parts[2].trimmed();
		Doc d(name, keywords, content);
		docs.push_back(d);
	}
	fin.close();
}

void Repo::sortByName()
{
	sort(docs.begin(), docs.end(), [](Doc d1, Doc d2) { return d1.getName() < d2.getName(); });
}

Repo::Repo()
{
	loadFromFile();
	sortByName();
}

std::vector<Doc> Repo::getDocs(QString str)
{
	if (str == "")
		return docs;
	std::vector<Doc> res;
	for (auto d : docs)
	{
		if (d.toString().contains(str))
			res.push_back(d);
	}
	return res;
}

Doc Repo::bestMatch(QString str)
{
	if (str == "")
		throw std::exception("No input received");

	std::vector<Doc> res;
	for (auto d : docs)
	{
		if (d.getName().contains(str))
			res.push_back(d);
	}
	if (res.size() == 0)
		throw std::exception("No matching name found");

	double max_similar = 0;
	Doc best_match = res[0];
	for (auto d : res)
	{
		double similar = (double)str.length() / d.getName().length();
		if (similar > max_similar)
		{
			max_similar = similar;
			best_match = d;
		}
	}
	return best_match;
}
