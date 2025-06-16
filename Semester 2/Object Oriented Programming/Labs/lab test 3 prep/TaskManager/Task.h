#pragma once
#include <QString>
class Task
{
private:
	QString description;
	int duration;
	int priority;

public:
	Task(QString description, int duration, int priority)
		: description(description), duration(duration), priority(priority) {}

	QString getDescription() const { return description; }
	int getDuration() const { return duration; }
	int getPriority() const { return priority; }

	void setDescription(QString description) { this->description = description; }
	void setDuration(int duration) { this->duration = duration; }
	void setPriority(int priority) { this->priority = priority; }

	QString toString() const { return description + "|" + QString::number(duration) + "|" + QString::number(priority); }
};

