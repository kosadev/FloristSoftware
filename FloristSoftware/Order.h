#pragma once
#include "pch.h"
#include "DbConnector.h"
#include "Product.h"

class Order
{
public:
	enum OrderState {
		Ordered,
		Confirmed
	};

	Order() {};
	Order(int id, int userId, OrderState orderState);

	static void showOrder(int id, DbConnector &db);
	static void showAll(DbConnector &db);
	static void showAll(OrderState OrderState, DbConnector &db);
	static void showAllOrdersByUser(int userID, DbConnector &db);

	static int countRecords(DbConnector &db);

	static ModificationResult addOrder(int userID, DbConnector &db);

	static ModificationResult confirmOrder(int id, DbConnector &db);
	static Order getOrder(int id, DbConnector &db);

	int getId() const;
	int getUserId() const;

	OrderState getOrderState() const;

	
private:
	int _id = -1;
	int _userID;
	OrderState _orderState;

};