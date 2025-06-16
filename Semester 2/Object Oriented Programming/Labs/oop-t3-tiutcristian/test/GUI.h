#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include "Repo.h"

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(Repo repo, QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUIClass ui;
    Repo repo;

    void populateList();
    void connectSignalsAndSlots();

    void filterMedications();
    void displayEffects();
};
