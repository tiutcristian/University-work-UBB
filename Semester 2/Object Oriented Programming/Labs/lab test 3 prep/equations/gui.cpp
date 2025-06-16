#include "gui.h"

gui::gui(Repo* repo, QWidget *parent)
    : repo(repo), QWidget(parent)
{
    ui.setupUi(this);
    connectComponents();
    populateList();
}

gui::~gui()
{}

void gui::connectComponents()
{
    connect(ui.eqList, &QListView::clicked, this, &gui::equationClickedHandler);
    connect(ui.updateButton, &QPushButton::clicked, this, &gui::updateButtonHandler);
	connect(ui.computeButton, &QPushButton::clicked, this, &gui::computeButtonHandler);
}

void gui::populateList()
{
    ui.eqList->setModel(repo.get());
}

void gui::equationClickedHandler()
{
    int index = ui.eqList->currentIndex().row();
	Equation eq = repo->getEquations()[index];
	ui.aLineEdit->setText(QString::number(eq.getA()));
	ui.bLineEdit->setText(QString::number(eq.getB()));
	ui.cLineEdit->setText(QString::number(eq.getC()));
}

void gui::updateButtonHandler()
{
    int index = ui.eqList->currentIndex().row();
	double a = ui.aLineEdit->text().toDouble();
	double b = ui.bLineEdit->text().toDouble();
	double c = ui.cLineEdit->text().toDouble();
	repo->updateEquation(a, b, c, index);
	repo->dataChanged(repo->index(index), repo->index(index));
}

void gui::computeButtonHandler()
{
	int index = ui.eqList->currentIndex().row();
	Equation eq = repo->getEquations()[index];
	std::pair<QString, QString> roots = eq.getRoots();
	ui.sol1->setText(roots.first);
	ui.sol2->setText(roots.second);
}
