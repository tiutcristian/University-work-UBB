#include "GUI.h"
#include <QMessageBox>

GUI::GUI(Department dep, Session& session, QWidget *parent)
    : QMainWindow(parent), dep(dep), session(session)
{
    ui.setupUi(this);
    session.registerObserver(this);
    setupInterface();
    connectComponents();
}

void GUI::update()
{
    ui.assignedList->clear();
    ui.unassignedList->clear();
    std::vector<QString> volunteersOfDep;
    for(auto v : session.getVolunteers())
	{
        if (v.getDepartment() == dep.getName())
            volunteersOfDep.push_back(v.toString());
        else if (v.getDepartment() == "-")
            ui.unassignedList->addItem(v.toString());
	}
	sort(volunteersOfDep.begin(), volunteersOfDep.end());
	for (auto v : volunteersOfDep)
		ui.assignedList->addItem(v);
}

void GUI::setupInterface()
{
    setWindowTitle(dep.getName());
    ui.descLabel->setText("Description: " + dep.getDesc());
    update();
}

void GUI::connectComponents()
{
    connect(ui.addButton, &QPushButton::clicked, this, &GUI::addButtonClicked);
    connect(ui.assignButton, &QPushButton::clicked, this, &GUI::assignButtonClicked);
    connect(qApp, &QCoreApplication::aboutToQuit, this, &GUI::aboutToQuitHandler);
    connect(ui.topButton, &QPushButton::clicked, this, &GUI::topHandler);
    connect(ui.resetButton, &QPushButton::clicked, this, &GUI::update);
}

void GUI::addButtonClicked()
{
    QString name = ui.nameLineEdit->text();
    QString email = ui.emailLineEdit->text();
    if (name == "" || email == "")
	{
		QMessageBox::warning(this, "Warning", "Name and email must be filled in!");
		return;
	}
    ui.descLabel->setText("not ok");
    QStringList interests = ui.interestsLineEdit->text().split(",");
    std::vector<QString> interestsVector;
    for(auto i : interests)
		interestsVector.push_back(i.trimmed());
    session.addVolunteer(Volunteer(name, email, interestsVector));
	ui.nameLineEdit->clear();
	ui.emailLineEdit->clear();
	ui.interestsLineEdit->clear();
}

void GUI::assignButtonClicked()
{
	if (ui.unassignedList->selectedItems().isEmpty())
	{
		QMessageBox::warning(this, "Warning", "No volunteer selected!");
		return;
	}
	QString name = ui.unassignedList->selectedItems().at(0)->text();
	name = name.split("|")[0].trimmed();
    session.assign(name, dep.getName());
}

void GUI::aboutToQuitHandler()
{
    session.writeToFile();
}

void GUI::topHandler()
{
    std::vector<Volunteer> top3 = session.getTop3(dep);
    ui.unassignedList->clear();
    for (int i = 0; i < 3 && i < top3.size(); i++)
		ui.unassignedList->addItem(top3[i].toString() + QString::number(session.getScore(top3[i], dep)));
}
