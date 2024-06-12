#include "Bill.h"

QString Bill::toString()
{
	QString str = "";
	str += this->company + "; ";
	str += this->serialNumber + "; ";
	str += QString::number(this->sum) + "; ";
	str += this->isPaid ? "true" : "false";
	return str;
}
