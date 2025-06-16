#pragma once
#include <vector>
#include "../Domain/Domain.h"
#include <QAbstractTableModel>

class Basket : public QAbstractTableModel
{
	Q_OBJECT

protected:
	std::vector<Coat> shoppingBasket;

	int findCoat(char size, const std::string& color);

public:
	explicit Basket(QObject* parent = nullptr) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	inline Coat& operator[](int pos) { return this->shoppingBasket[pos]; }
	int getSize() const { return (int)this->shoppingBasket.size(); }
	void addCoat(const Coat& coat);
	std::string toString();

	static void testBasket();
};