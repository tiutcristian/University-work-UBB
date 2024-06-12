#include "GUI.h"
#include <QMessageBox>

GUI::GUI(Repo repo, QWidget *parent)
    : QWidget(parent), repo(repo)
{
    ui.setupUi(this);
    this->populateList();
    this->connectSignalsAndSlots();
}

GUI::~GUI()
{}

void GUI::populateList()
{
    for (auto& e : this->repo.getMedications())
		this->ui.medicationList->addItem(e.toString());
}

void GUI::connectSignalsAndSlots()
{
    connect(ui.searchLineEdit, &QLineEdit::textChanged, this, &GUI::filterMedications);
    connect(ui.showButton, &QPushButton::clicked, this, &GUI::displayEffects);
}

void GUI::filterMedications()
{
	this->ui.medicationList->clear();
	QString str = ui.searchLineEdit->text();
    std::vector<Medication> medications = this->repo.getMedications(str);
    for (auto& e : medications)
		this->ui.medicationList->addItem(e.toString());
}

void GUI::displayEffects()
{
	this->ui.effectsList->clear();
    QString name = this->ui.medicationLineEdit->text();
	try
	{
		std::vector<QString> effects = this->repo.getEffectsByName(name);
		for (auto& e : effects)
			this->ui.effectsList->addItem(e);
	}
	catch (const std::exception& e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
}
