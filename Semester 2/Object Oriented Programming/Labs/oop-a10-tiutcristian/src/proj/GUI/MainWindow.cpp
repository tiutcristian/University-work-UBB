#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "AdminWindow.h"
#include "UserWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(Services& serv) : serv(serv)
{
	setupUi();
	createOperatingModeSelector();
	connectComponents();
}

MainWindow::~MainWindow()
{
    delete adminButton;
	delete userButton;
    delete exitButton;
}

void MainWindow::setupUi()
{
    this->setWindowTitle("Mainwindow");
	this->resize(600, 400);
    this->setCentralWidget(new QWidget(this));
}

void MainWindow::connectComponents()
{
    connect(adminButton, SIGNAL(clicked()), this, SLOT(onAdminButtonClicked()));
    connect(userButton, SIGNAL(clicked()), this, SLOT(onUserButtonClicked()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void MainWindow::createOperatingModeSelector()
{
    QLabel* titleLabel = new QLabel("Coats", this);
    titleLabel->setStyleSheet("font-size: 40px; font-style: italic;");
    titleLabel->setAlignment(Qt::AlignCenter);
    QLabel* operatingModeLabel = new QLabel("Select operating mode", this);
    adminButton = new QPushButton("Admin", this);
    userButton = new QPushButton("User", this);
    exitButton = new QPushButton("Exit", this);
    

    QVBoxLayout* modeButtonsLayout = new QVBoxLayout();
    modeButtonsLayout->addStretch();
    modeButtonsLayout->addWidget(titleLabel);
    modeButtonsLayout->addWidget(operatingModeLabel);
    modeButtonsLayout->addWidget(adminButton);
    modeButtonsLayout->addWidget(userButton);
    modeButtonsLayout->addWidget(exitButton);
    modeButtonsLayout->addStretch();

    QWidget* mainWidget = new QWidget(this);
    mainWidget->setLayout(modeButtonsLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addStretch();
    mainLayout->addWidget(mainWidget);
    mainLayout->addStretch();

    this->centralWidget()->setLayout(mainLayout);
}

void MainWindow::onAdminButtonClicked()
{
    AdminWindow* adminWindow = new AdminWindow(serv, this);
    adminWindow->show();
	this->close();
}

void MainWindow::onUserButtonClicked()
{
    QMessageBox msgBox;
    msgBox.setText("Choose a format to save your shopping basket:");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton* csvButton = msgBox.addButton("CSV", QMessageBox::ActionRole);
    QPushButton* htmlButton = msgBox.addButton("HTML", QMessageBox::ActionRole);
    msgBox.exec();

    char choice = (msgBox.clickedButton() == csvButton) ? 'c' : 'h';
    UserWindow* userWindow = new UserWindow(serv, choice, this);
    userWindow->show();
    this->close();
}
