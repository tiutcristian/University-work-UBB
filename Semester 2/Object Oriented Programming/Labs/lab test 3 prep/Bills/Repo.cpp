#include "Repo.h"
#include <fstream>
#include <QStringList>
#include <algorithm>

void Repo::readFromFile()
{
	std::ifstream file("bills.txt");
	std::string line;
	while (std::getline(file, line))
	{
		QStringList tokens = QString::fromStdString(line).split(";");
		QString company = tokens[0].trimmed();
		QString serialNumber = tokens[1].trimmed();
		double sum = tokens[2].trimmed().toDouble();
		bool isPaid = tokens[3].trimmed() == "true";
		bills.push_back(Bill{ company, serialNumber, sum, isPaid });
	}
	file.close();
}

void Repo::sortByCompany()
{
	sort(bills.begin(), bills.end(), [](Bill a, Bill b) {
		return a.getCompany() < b.getCompany();
		});
}

Repo::Repo()
{
	readFromFile();
	sortByCompany();
}

double Repo::getTotalUnpaidByCompany(QString company)
{
	double total = 0;
	bool found = false;
	for (auto bill : bills)
		if (bill.getCompany() == company)
		{
			found = true;
			if(!bill.getIsPaid())
				total += bill.getSum();
		}
	if (!found)
		throw std::exception("Company not found");
	return total;
}

std::vector<Bill> Repo::getBillsByPaid(bool paid)
{
	std::vector<Bill> billsByPaid;
	for (auto bill : bills)
		if (bill.getIsPaid() == paid)
			billsByPaid.push_back(bill);
	return billsByPaid;
}
