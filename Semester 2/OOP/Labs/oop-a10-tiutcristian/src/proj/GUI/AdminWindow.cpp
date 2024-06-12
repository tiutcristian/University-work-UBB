#include "AdminWindow.h"
#include <fstream>
#include <QString>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QShortcut>


void AdminWindow::buildUi()
{
	init();
	createForm();
	createTools();
	updateCoatsList();

	mainLayout->addWidget(formWidget);
	mainLayout->addWidget(toolsWidget);
	mainLayout->addWidget(listWidget);

	this->undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
	this->redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);

	setLayout(mainLayout);
}

void AdminWindow::connectComponents()
{
	connect(backButton, &QPushButton::clicked, this, &AdminWindow::onBackButtonClicked);
	connect(listWidget, &QListWidget::itemSelectionChanged, this, &AdminWindow::itemSelected);
	connect(addButton, &QPushButton::clicked, this, &AdminWindow::onAddButtonClicked);
	connect(updateButton, &QPushButton::clicked, this, &AdminWindow::onUpdateButtonClicked);
	connect(deleteButton, &QPushButton::clicked, this, &AdminWindow::onDeleteButtonClicked);
	connect(chartButton, &QPushButton::clicked, this, &AdminWindow::onChartButtonClicked);
	connect(undoButton, &QPushButton::clicked, this, &AdminWindow::onUndoButtonClicked);
	connect(redoButton, &QPushButton::clicked, this, &AdminWindow::onRedoButtonClicked);
	connect(undoShortcut, &QShortcut::activated, this, &AdminWindow::onUndoButtonClicked);
	connect(redoShortcut, &QShortcut::activated, this, &AdminWindow::onRedoButtonClicked);
}

void AdminWindow::updateCoatsList()
{
	for (auto coat : serv.getElements())
	{
		QString item = QString::fromStdString(coat.toString());
		listWidget->addItem(item);
	}
}

void AdminWindow::createForm()
{
	sizeLabel->setText("Size:");
	colorLabel->setText("Color:");
	priceLabel->setText("Price:");
	quantityLabel->setText("Quantity:");
	linkLabel->setText("Link:");

	sizeLabel->setBuddy(sizeComboBox);
	colorLabel->setBuddy(colorLineEdit);
	priceLabel->setBuddy(priceLineEdit);
	quantityLabel->setBuddy(quantityLineEdit);
	linkLabel->setBuddy(linkLineEdit);

	sizeComboBox->addItem("S");
	sizeComboBox->addItem("M");
	sizeComboBox->addItem("L");
	sizeComboBox->setCurrentIndex(0);

	colorLineEdit->setPlaceholderText("Enter color here...");
	priceLineEdit->setPlaceholderText("Enter price here...");
	quantityLineEdit->setPlaceholderText("Enter quantity here...");
	linkLineEdit->setPlaceholderText("Enter link here...");

	formLayout->addRow(sizeLabel, sizeComboBox);
	formLayout->addRow(colorLabel, colorLineEdit);
	formLayout->addRow(priceLabel, priceLineEdit);
	formLayout->addRow(quantityLabel, quantityLineEdit);
	formLayout->addRow(linkLabel, linkLineEdit);

	formWidget->setLayout(formLayout);
}

void AdminWindow::createTools()
{
	addButton->setText("Add");
	updateButton->setText("Update");
	deleteButton->setText("Delete");
	undoButton->setText("Undo");
	redoButton->setText("Redo");
	chartButton->setText("Chart");
	backButton->setText("Back");

	toolsLayout->addStretch();
	toolsLayout->addWidget(addButton);
	toolsLayout->addWidget(updateButton);
	toolsLayout->addWidget(deleteButton);
	toolsLayout->addWidget(undoButton);
	toolsLayout->addWidget(redoButton);
	toolsLayout->addWidget(chartButton);
	toolsLayout->addWidget(backButton);
	toolsLayout->addStretch();
	toolsWidget->setLayout(toolsLayout);
}

void AdminWindow::init()
{
	mainLayout = new QHBoxLayout;
	formLayout = new QFormLayout;
	formWidget = new QWidget;
	sizeLabel = new QLabel;
	sizeComboBox = new QComboBox;
	colorLabel = new QLabel;
	colorLineEdit = new QLineEdit;
	priceLabel = new QLabel;
	priceLineEdit = new QLineEdit;
	quantityLabel = new QLabel;
	quantityLineEdit = new QLineEdit;
	linkLabel = new QLabel;
	linkLineEdit = new QLineEdit;
	toolsLayout = new QVBoxLayout;
	toolsWidget = new QWidget;
	addButton = new QPushButton;
	updateButton = new QPushButton;
	deleteButton = new QPushButton;
	chartButton = new QPushButton;
	backButton = new QPushButton;
	listWidget = new QListWidget;
	undoButton = new QPushButton;
	redoButton = new QPushButton;
}

void AdminWindow::setupWindow()
{
	this->setWindowTitle("Admin Window");
}

void AdminWindow::unsetForm()
{
	sizeComboBox->setCurrentIndex(0);
	colorLineEdit->clear();
	priceLineEdit->clear();
	quantityLineEdit->clear();
	linkLineEdit->clear();
}

void AdminWindow::onBackButtonClicked()
{
	parent->show();
	this->close();
}

void AdminWindow::itemSelected()
{
	QListWidgetItem* item = listWidget->currentItem();
	if (item == nullptr)
		return;
	QStringList tokens = item->text().split(" ");
	sizeComboBox->setCurrentText(tokens[0]);
	colorLineEdit->setText(tokens[1]);
	priceLineEdit->setText(tokens[2]);
	quantityLineEdit->setText(tokens[3]);
	linkLineEdit->setText(tokens[4]);
}

void AdminWindow::onAddButtonClicked()
{
	QString size = sizeComboBox->currentText();
	QString color = colorLineEdit->text();
	QString price = priceLineEdit->text();
	QString quantity = quantityLineEdit->text();
	QString link = linkLineEdit->text();
	if (size.isEmpty() || color.isEmpty() || price.isEmpty() || quantity.isEmpty() || link.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "All fields must be filled!");
		return;
	}
	try
	{
		serv.add(size.toStdString()[0], color.toStdString(), price.toDouble(), quantity.toInt(), link.toStdString());
		listWidget->clear();
		updateCoatsList();
		unsetForm();
	}
	catch (std::exception& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}

void AdminWindow::onUpdateButtonClicked()
{
	QString size = sizeComboBox->currentText();
	QString color = colorLineEdit->text();
	QString price = priceLineEdit->text();
	QString quantity = quantityLineEdit->text();
	QString link = linkLineEdit->text();
	if (size.isEmpty() || color.isEmpty() || price.isEmpty() || quantity.isEmpty() || link.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "All fields must be filled!");
		return;
	}
	try
	{
		serv.update(size.toStdString()[0], color.toStdString(), price.toDouble(), quantity.toInt(), link.toStdString());
		listWidget->clear();
		updateCoatsList();
		unsetForm();
	}
	catch (std::exception& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}

void AdminWindow::onDeleteButtonClicked()
{
	QString size = sizeComboBox->currentText();
	QString color = colorLineEdit->text();
	QString price = priceLineEdit->text();
	QString quantity = quantityLineEdit->text();
	QString link = linkLineEdit->text();
	if (size.isEmpty() || color.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "All fields must be filled!");
		return;
	}
	try
	{
		serv.remove(size.toStdString()[0], color.toStdString());
		listWidget->clear();
		updateCoatsList();
		unsetForm();
	}
	catch (std::exception& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}

void AdminWindow::onChartButtonClicked()
{
	QBarSeries* series = new QBarSeries();
	QBarSet* set = new QBarSet("Coats");
	*set << serv.getQuantityBySize('S') 
		 << serv.getQuantityBySize('M') 
		 << serv.getQuantityBySize('L');
	series->append(set);

	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Coats by Size");
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QStringList categories;
	categories << "S" << "M" << "L";
	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	QValueAxis* axisY = new QValueAxis();
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	QChartView* chartView = new QChartView(chart);
	chartView->setChart(chart);

	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->resize(400, 300);
	chartView->setWindowTitle("Coats by Size");
	chartView->show();
}

void AdminWindow::onUndoButtonClicked()
{
	try
	{
		serv.undo();
		listWidget->clear();
		updateCoatsList();
	}
	catch (std::exception& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}

void AdminWindow::onRedoButtonClicked()
{
	try
	{
		serv.redo();
		listWidget->clear();
		updateCoatsList();
	}
	catch (std::exception& e)
	{
		QMessageBox::warning(this, "Warning", e.what());
	}
}

AdminWindow::AdminWindow(Services& serv, QWidget *parent) : serv(serv), parent(parent)
{
	setupWindow();
	buildUi();
	connectComponents();
}

AdminWindow::~AdminWindow()
{
	delete mainLayout;
	delete formLayout;
	delete formWidget;
	delete sizeLabel;
	delete sizeComboBox;
	delete colorLabel;
	delete colorLineEdit;
	delete priceLabel;
	delete priceLineEdit;
	delete quantityLabel;
	delete quantityLineEdit;
	delete linkLabel;
	delete linkLineEdit;
	delete toolsLayout;
	delete toolsWidget;
	delete addButton;
	delete updateButton;
	delete deleteButton;
	delete chartButton;
	delete backButton;
	delete listWidget;
	delete undoButton;
	delete redoButton;
	delete undoShortcut;
	delete redoShortcut;
}
