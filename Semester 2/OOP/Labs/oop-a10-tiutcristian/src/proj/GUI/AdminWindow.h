#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include "../Services/Services.h"

class AdminWindow : public QWidget
{
	Q_OBJECT

private:
	Services& serv;

	QWidget* parent;
	QHBoxLayout* mainLayout;
	QFormLayout* formLayout;
	QWidget* formWidget;
	QLabel* sizeLabel;
	QComboBox* sizeComboBox;
	QLabel* colorLabel;
	QLineEdit* colorLineEdit;
	QLabel* priceLabel;
	QLineEdit* priceLineEdit;
	QLabel* quantityLabel;
	QLineEdit* quantityLineEdit;
	QLabel* linkLabel;
	QLineEdit* linkLineEdit;
	QVBoxLayout* toolsLayout;
	QWidget* toolsWidget;
	QPushButton* addButton;
	QPushButton* updateButton;
	QPushButton* deleteButton;
	QPushButton* chartButton;
	QPushButton* backButton;
	QListWidget* listWidget;
	QPushButton* undoButton;
	QPushButton* redoButton;
	QShortcut* undoShortcut;
	QShortcut* redoShortcut;


	void buildUi();
	void connectComponents();
	void updateCoatsList();
	void createForm();
	void createTools();
	void init();
	void setupWindow();
	void unsetForm();

private slots:
	void onBackButtonClicked();
	void itemSelected();
	void onAddButtonClicked();
	void onUpdateButtonClicked();
	void onDeleteButtonClicked();
	void onChartButtonClicked();
	void onUndoButtonClicked();
	void onRedoButtonClicked();

public:
	AdminWindow(Services& serv, QWidget* parent = nullptr);
	~AdminWindow();
};
