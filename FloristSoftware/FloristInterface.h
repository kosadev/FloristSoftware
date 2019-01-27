#pragma once
#include "pch.h"
#include "DbConnector.h"
#include "Order.h"
#include "User.h"
#include "Product.h"


class FloristInterface
{
public:
	FloristInterface(DbConnector &db);
	~FloristInterface();

	bool addProductToBasket();
	bool addOrder(int userID);

	void showBasket(int userID);
	void showOrdersHistory(int userID);
	void showProducts();

	void showOrderPositions(int orderId, DbConnector &db);


	DbConnector _db;
	std::vector<Product> _products{
		Product(0, (std::string)"Red rose", 12),
		Product(1, (std::string)"Blue rose", 15),
		Product(2, (std::string)"Black rose", 9.99),
		Product(3, (std::string)"Yellow tulip", 4),
		Product(4, (std::string)"Snowdrop", 3),
		Product(5, (std::string)"Bouqet", 68),
		Product(6, (std::string)"Sweet basket", 119.99),
		Product(7, (std::string)"Wine bottle", 77),
		Product(8, (std::string)"Golden chrysanthemumse", 0.5)
	};

	std::vector<Product> _basket;
};

