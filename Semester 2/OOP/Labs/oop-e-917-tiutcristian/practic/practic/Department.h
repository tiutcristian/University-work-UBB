#pragma once
#include <QString>
class Department
{
private:
	QString name;
	QString desc;
public:
	Department(QString name, QString desc) 
		: name(name), desc(desc) {}
	QString getName() const { return name; }
	QString getDesc() const { return desc; }
	void setName(QString name) { this->name = name; }
	void setDesc(QString desc) { this->desc = desc; }
};

