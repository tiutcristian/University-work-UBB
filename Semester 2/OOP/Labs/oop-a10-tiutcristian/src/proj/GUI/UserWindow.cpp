#include "UserWindow.h"
#include "../Basket/CSVBasket.h"
#include "../Basket/HTMLBasket.h"
#include "../Repository/Repository.h"
#include <QMessageBox>

void UserWindow::setupWindow()
{
	setWindowTitle("User Window");
}

void UserWindow::init()
{
	mainLayout = new QVBoxLayout;
	upperLayout = new QHBoxLayout;
	modeLabel = new QLabel;
	crtLabel = new QLabel;
	sumLabel = new QLabel;
	controlLayout = new QHBoxLayout;
	sizeComboBox = new QComboBox;
	startButton = new QPushButton;
	endButton = new QPushButton;
	addButton = new QPushButton;
	nextButton = new QPushButton;
	viewAllButton = new QPushButton;
	backButton = new QPushButton;
}

void UserWindow::buildUpperLayout()
{
	QString modeText = (mode == 'c') ? "[CSV]" : "[HTML]";
	modeLabel->setText("Mode: " + modeText);

	mainLayout->addWidget(modeLabel);
}

void UserWindow::buildCrtLayout()
{
	crtLabel->setText("[Select a size and start the session]");
	sumLabel->setText("");

	mainLayout->addWidget(crtLabel);
	mainLayout->addWidget(sumLabel);
}

void UserWindow::buildControlLayout()
{
	sizeComboBox->addItem("-");
	sizeComboBox->addItem("S");
	sizeComboBox->addItem("M");
	sizeComboBox->addItem("L");

	startButton->setText("Start");

	addButton->setText("Add");
	nextButton->setText("Next");
	viewAllButton->setText("View all");
	endButton->setText("End");
	backButton->setText("Back");

	controlLayout->addWidget(sizeComboBox);
	controlLayout->addWidget(startButton);
	controlLayout->addWidget(endButton);
	controlLayout->addWidget(addButton);
	controlLayout->addWidget(nextButton);
	controlLayout->addWidget(viewAllButton);
	controlLayout->addWidget(backButton);
	controlLayout->addStretch();

	mainLayout->addLayout(controlLayout);
}

void UserWindow::buildUi()
{
	init();
	buildUpperLayout();
	buildCrtLayout();
	buildControlLayout();
	setLayout(mainLayout);
	initialState();
}

void UserWindow::connectComponents()
{
	connect(backButton, &QPushButton::clicked, this, &UserWindow::onBackButtonClicked);
	connect(startButton, &QPushButton::clicked, this, &UserWindow::onStartButtonClicked);
	connect(endButton, &QPushButton::clicked, this, &UserWindow::onEndButtonClicked);
	connect(addButton, &QPushButton::clicked, this, &UserWindow::onAddButtonClicked);
	connect(nextButton, &QPushButton::clicked, this, &UserWindow::onNextButtonClicked);
	connect(viewAllButton, &QPushButton::clicked, this, &UserWindow::onViewAllButtonClicked);
}

void UserWindow::initialState()
{
	crtLabel->setText("[Select a size and start the session]");
	sumLabel->setText("");
	endButton->setEnabled(false);
	addButton->setEnabled(false);
	nextButton->setEnabled(false);
	viewAllButton->setEnabled(false);
	startButton->setEnabled(true);
	sizeComboBox->setEnabled(true);
}

void UserWindow::onStartButtonClicked()
{
	endButton->setEnabled(true);
	addButton->setEnabled(true);
	nextButton->setEnabled(true);
	viewAllButton->setEnabled(true);
	startButton->setEnabled(false);
	sizeComboBox->setEnabled(false);
	char size = sizeComboBox->currentText().toStdString()[0];
	filteredRepo = this->serv.filterBySize(size);
	crtPos = 0;
	crtSum = 0;
	if (mode == 'c')
		basket = make_unique<CSVBasket>("basket.csv");
	else
		basket = make_unique<HTMLBasket>("basket.html");
	crtLabel->setText(("Current coat: " + filteredRepo[crtPos].toString()).c_str());
	sumLabel->setText(("Current sum: " + to_string(crtSum)).c_str());
}

void UserWindow::onEndButtonClicked()
{
	// If button "Ok" pressed, perform onViewAllButtonClicked()
	if (basket->getSize()) {
		QMessageBox::information(this, "Information", "Session ended! "
			"You have bought the following coats:\n\n"
			+ QString::fromStdString(basket->toString()), QMessageBox::Ok);
		basket->displayBasket();
	}
	else
		QMessageBox::information(this, "Information", "No coats bought!");
	
	initialState();
}

void UserWindow::onAddButtonClicked()
{
	if (filteredRepo[crtPos].getQuantity() == 0)
		QMessageBox::warning(this, "Warning", "Coat out of stock!");
	else
	{
		Coat coat = filteredRepo[crtPos];
		coat.setQuantity(1);
		basket->addCoat(coat);
		basket->writeToFile();
		filteredRepo[crtPos].setQuantity(filteredRepo[crtPos].getQuantity() - 1);
		this->serv.decrementQuantity(coat.getSize(), coat.getColor());
		crtSum += filteredRepo[crtPos].getPrice();
		sumLabel->setText(("Current sum: " + to_string(crtSum)).c_str());
	}
	onNextButtonClicked();
}

void UserWindow::onNextButtonClicked()
{
	crtPos = (crtPos + 1) % filteredRepo.getSize();
	crtLabel->setText(("Current coat: " + filteredRepo[crtPos].toString()).c_str());
}

void UserWindow::onViewAllButtonClicked()
{
	QTableView* view = new QTableView;
	view->setModel(basket.get());
	view->resize(600, 400);
	view->show();
}

UserWindow::UserWindow(Services& serv, char mode, QWidget *parent) : serv(serv), mode(mode), parent(parent)
{
	setupWindow();
	buildUi();
	connectComponents();
}

UserWindow::~UserWindow()
{
	delete mainLayout;
	delete upperLayout;
	delete modeLabel;
	delete crtLabel;
	delete sumLabel;
	delete controlLayout;
	delete sizeComboBox;
	delete startButton;
	delete endButton;
	delete addButton;	
	delete nextButton;
	delete viewAllButton;
	delete backButton;
}

void UserWindow::onBackButtonClicked()
{
	parent->show();
	this->close();
}
