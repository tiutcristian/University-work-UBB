#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QTableView>
#include "../Services/Services.h"

class UserWindow  : public QWidget
{
	Q_OBJECT

private:
	QWidget* parent;
	QVBoxLayout* mainLayout;
	QHBoxLayout* upperLayout;
	QLabel* modeLabel;
	QLabel* crtLabel;
	QLabel* sumLabel;
	QHBoxLayout* controlLayout;
	QComboBox* sizeComboBox;
	QPushButton* startButton;
	QPushButton* endButton;
	QPushButton* addButton;
	QPushButton* nextButton;
	QPushButton* viewAllButton;
	QPushButton* backButton;

	Services& serv;
	
	char mode;

	Repository filteredRepo;
	int crtPos;
	double crtSum;
	unique_ptr<FileBasket> basket;

	void setupWindow();
	void init();
	void buildUpperLayout();
	void buildCrtLayout();
	void buildControlLayout();
	void buildUi();
	void connectComponents();
	void initialState();

private slots:
	void onBackButtonClicked();
	void onStartButtonClicked();
	void onEndButtonClicked();
	void onAddButtonClicked();
	void onNextButtonClicked();
	void onViewAllButtonClicked();

public:
	UserWindow(Services& serv, char mode, QWidget *parent = nullptr);
	~UserWindow();
};
