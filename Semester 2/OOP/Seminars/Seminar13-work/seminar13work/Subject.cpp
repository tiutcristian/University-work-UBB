#include "Subject.h"

void Subject::registerObserver(Observer* observer)
{
	observers.push_back(observer);
}

void Subject::unregisterObserver(Observer* observer)
{
	for (int i = 0; i < observers.size(); i++)
	{
		if (observers[i] == observer)
		{
			observers.erase(observers.begin() + i);
			break;
		}
	}
}

void Subject::notify()
{
	for (auto observer : observers)
	{
		observer->update();
	}
}
