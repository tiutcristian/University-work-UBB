#pragma once
#include <QString>

class Bill
{
private:
	QString company;
	QString serialNumber;
	double sum;
	bool isPaid;

public:
	Bill(QString company, QString serialNumber, double sum, bool isPaid)
		: company{ company }, 
		serialNumber{ serialNumber }, 
		sum{ sum }, 
		isPaid{ isPaid } {}

	QString getCompany() { return company; }
	QString getSerialNumber() { return serialNumber; }
	double getSum() { return sum; }
	bool getIsPaid() { return isPaid; }

	void setCompany(QString company) { this->company = company; }
	void setSerialNumber(QString serialNumber) { this->serialNumber = serialNumber; }
	void setSum(double sum) { this->sum = sum; }
	void setIsPaid(bool isPaid) { this->isPaid = isPaid; }

	QString toString();
};

