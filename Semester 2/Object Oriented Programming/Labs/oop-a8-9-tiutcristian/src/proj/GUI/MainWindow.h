#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "../Services/Services.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Services& serv);
    ~MainWindow();

private:
    Services& serv;

    QPushButton* adminButton;
    QPushButton* userButton;
    QPushButton* exitButton;

    void setupUi();
    void connectComponents();
    void createOperatingModeSelector();

private slots:
    void onAdminButtonClicked();
	void onUserButtonClicked();
};
