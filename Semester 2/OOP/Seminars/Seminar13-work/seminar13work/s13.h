#pragma once

#include <QtWidgets/QWidget>
#include "ui_s13.h"

class s13 : public QWidget
{
    Q_OBJECT

public:
    s13(QWidget *parent = nullptr);
    ~s13();

private:
    Ui::s13Class ui;
};
