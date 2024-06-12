#pragma once
#include <vector>
#include "Observer.h"
class Subject
{
private:
	std::vector<Observer*> observers;

public:
	void registerObserver(Observer* obs) { observers.push_back(obs); }
	void notify()
	{
		for (auto& obs : observers)
			obs->update();
	}
};

