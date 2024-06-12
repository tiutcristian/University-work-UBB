#include "GUI.h"
#include <QMessageBox>


GUI::GUI(Repo repo, QWidget *parent)
    : QMainWindow(parent), repo{repo}
{
    ui.setupUi(this);
    populateList();
    connectComponents();
    ui.allBox->setChecked(true);
}

GUI::~GUI()
{}

void GUI::populateList()
{
    ui.billsList->clear();
    for (auto bill : repo.getBills()) {
        ui.billsList->addItem(bill.toString());
        if (!bill.getIsPaid()) {
			ui.billsList->item(ui.billsList->count() - 1)->setBackground(Qt::red);
		}
    }
		
}

void GUI::populatePaid()
{
    ui.billsList->clear();
    for (auto bill : repo.getBillsByPaid(true)) {
		ui.billsList->addItem(bill.toString());
	}
}

void GUI::populateUnpaid()
{
    ui.billsList->clear();
    for (auto bill : repo.getBillsByPaid(false)) {
		ui.billsList->addItem(bill.toString());
		ui.billsList->item(ui.billsList->count() - 1)->setBackground(Qt::red);
	}
}

void GUI::connectComponents()
{
    connect(ui.paidBox, &QRadioButton::clicked, this, &GUI::populatePaid);
    connect(ui.unpaidBox, &QRadioButton::clicked, this, &GUI::populateUnpaid);
    connect(ui.allBox, &QRadioButton::clicked, this, &GUI::populateList);
    connect(ui.calculateButton, &QPushButton::clicked, this, &GUI::calculateTotal);
}

void GUI::calculateTotal()
{
    QString company = ui.companyLineEdit->text();
    try
    {
        double total = repo.getTotalUnpaidByCompany(company);
        ui.totalLabel->setText("Total: " + QString::number(total));
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}
