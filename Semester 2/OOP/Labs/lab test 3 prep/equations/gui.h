#pragma once

#include <QtWidgets/QWidget>
#include "ui_gui.h"
#include "Repo.h"

class gui : public QWidget
{
    Q_OBJECT

public:
    gui(Repo* repo, QWidget *parent = nullptr);
    ~gui();

private:
    Ui::guiClass ui;
    std::unique_ptr<Repo> repo;
    void connectComponents();
    void populateList();
    void equationClickedHandler();
    void updateButtonHandler();
    void computeButtonHandler();
};
