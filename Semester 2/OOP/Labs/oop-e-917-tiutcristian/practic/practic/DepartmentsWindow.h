#pragma once

#include <QWidget>
#include "ui_DepartmentsWindow.h"
#include "Department.h"
#include "Session.h"

class DepartmentsWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	DepartmentsWindow(std::vector<Department>departments, Session& session, QWidget *parent = nullptr);

private:
	Ui::DepartmentsWindowClass ui;
	Session& session;
	std::vector<Department> departments;
	std::vector<int> volunteersCount;

	void update() override;
};
