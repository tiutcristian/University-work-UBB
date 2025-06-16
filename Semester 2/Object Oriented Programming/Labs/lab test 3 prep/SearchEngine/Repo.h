#pragma once
#include "Doc.h"

class Repo
{
private:
	std::vector<Doc> docs;
	
	void loadFromFile();
	void sortByName();

public:
	Repo();
	std::vector<Doc> getDocs(QString str = "");
	Doc bestMatch(QString str);

};

