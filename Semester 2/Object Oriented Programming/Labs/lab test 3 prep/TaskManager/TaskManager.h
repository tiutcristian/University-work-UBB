#pragma once

#include <QtWidgets/QWidget>
#include "ui_TaskManager.h"
#include "Repo.h"

class MySortFilterProxyModel : public QSortFilterProxyModel
{
private:
	std::string str;
public:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;
    MySortFilterProxyModel(std::string str, QObject* parent = nullptr): QSortFilterProxyModel(parent), str(str) {}
};

class TaskManager : public QWidget
{
    Q_OBJECT

public:
    TaskManager(Repo* repo, QWidget *parent = nullptr);
    ~TaskManager();

private:
    Ui::TaskManagerClass ui;
    std::unique_ptr<Repo> repo;
};