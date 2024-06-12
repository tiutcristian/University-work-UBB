#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "Repo.h"

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(Repo repo, QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUIClass ui;
    Repo repo;

    void populateList();
    void populatePaid();
    void populateUnpaid();
    void connectComponents();
    void calculateTotal();
};
