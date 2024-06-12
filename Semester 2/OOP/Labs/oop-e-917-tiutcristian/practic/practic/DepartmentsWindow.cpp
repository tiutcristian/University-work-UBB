#include "DepartmentsWindow.h"

DepartmentsWindow::DepartmentsWindow(std::vector<Department>departments, Session& session, QWidget *parent)
	: QWidget(parent), departments{departments}, session{session}
{
	ui.setupUi(this);
	session.registerObserver(this);
	update();
}

void DepartmentsWindow::update()
{
	ui.departmentsList->clear();	
	volunteersCount.clear();
	for (auto& dep : departments)
	{
		int count = 0;
		for (auto& v : session.getVolunteers())
			if (v.getDepartment() == dep.getName())
				count++;
		volunteersCount.push_back(count);
		ui.departmentsList->addItem(
			dep.getName() + " (" + QString::number(count) + " volunteers)"
		);
	}
}
