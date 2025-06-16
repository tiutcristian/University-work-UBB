#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "Department.h"
#include "Observer.h"
#include "Session.h"

class GUI : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    GUI(Department dep, Session& session, QWidget *parent = nullptr);
    void update() override;

private:
    Ui::GUIClass ui;
    Department dep;
    Session& session;

    void setupInterface();
    void connectComponents();
    void addButtonClicked();
    void assignButtonClicked();
    void aboutToQuitHandler();
    void topHandler();
};
