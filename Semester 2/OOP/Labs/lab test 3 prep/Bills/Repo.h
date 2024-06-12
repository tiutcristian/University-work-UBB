#pragma once
#include <vector>
#include "Bill.h"

class Repo
{
private:
	std::vector<Bill> bills;

	void readFromFile();
	void sortByCompany();

public:
	Repo();

	std::vector<Bill> getBills() { return bills; }
	double getTotalUnpaidByCompany(QString company);
	std::vector<Bill> getBillsByPaid(bool paid);
};

