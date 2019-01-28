#include "pch.h"
#include "Order.h"
#include "Order.h"


Order::Order(int id, int userId, OrderState orderState) :
	_id(id),
	_userID(userId),
	_orderState(orderState)
{
}

int Order::getId() const {
	return _id;
}

int Order::getUserId() const {
	return _userID;
}

Order::OrderState Order::getOrderState() const {
	return _orderState;
}

int Order::countRecords(DbConnector &db)
{
	return db.countRecords("Order");
}

void Order::showOrder(int id, DbConnector &db)
{
	std::string query = "SELECT * FROM Order WHERE Order_ID=" + std::to_string(id);
	MYSQL_ROW row;
	MYSQL_RES *res = db.executeQuery(query);
	int resultsAmount = 0;
	while (row = mysql_fetch_row(res))
	{
		resultsAmount++;
		OrderState orderState = (OrderState)atoi(row[4]);

		std::cout << "\n\tID: " << row[0];

		std::cout << ", Order status: ";

		switch (orderState) {
		case Ordered:
			std::cout << "Ordered";
			break;
		case Confirmed:
			std::cout << "Confirmed";
			break;
		}

		std::cout << std::endl;
	}
	if (resultsAmount == 0) {
		std::cout << "\tThere isn't Order with " << id << " ID" << std::endl;
	}
}

void Order::showAll(DbConnector &db)
{
	std::string query = "SELECT * FROM `Order` ORDER BY `Order_state`";
	MYSQL_ROW row;
	MYSQL_RES *res = db.executeQuery(query);
	int resultsAmount = 0;
	while (row = mysql_fetch_row(res))
	{
		resultsAmount++;

		OrderState orderState = (OrderState)atoi(row[2]);


		std::cout << "\n\tID: " << row[0];

		std::cout << ", Order status: ";

		switch (orderState) {
		case Ordered:
			std::cout << "Ordered";
			break;
		case Confirmed:
			std::cout << "Confirmed";
			break;
		}


		std::cout << std::endl;
	}
	if (resultsAmount == 0) {
		std::cout << "\tThere aren't any orders" << std::endl;
	}
}


void Order::showAll(Order::OrderState orderState, DbConnector &db)
{
	std::string query = "SELECT * FROM `Order` WHERE `Order_state`=" + std::to_string((int)orderState) + " ORDER BY `Order_state`";
	MYSQL_ROW row;
	MYSQL_RES *res = db.executeQuery(query);
	int resultsAmount = 0;
	while (row = mysql_fetch_row(res))
	{
		resultsAmount++;

		OrderState orderState = (OrderState)atoi(row[2]);

		std::cout << "\n\tID: " << row[0];

		std::cout << ", Order status: ";

		switch (orderState) {
		case Ordered:
			std::cout << "Ordered";
			break;
		case Confirmed:
			std::cout << "Confirmed";
			break;
		}
		std::cout << std::endl;
	}
	if (resultsAmount == 0) {
		std::cout << "\tThere aren't orders with " << orderState << " Order state" << std::endl;
	}
}

void Order::showAllOrdersByUser(int userID, DbConnector &db)
{
	std::string query = "SELECT * FROM Order WHERE User_ID_FK=" + std::to_string(userID) + " ORDER BY Order_state";
	MYSQL_ROW row;
	MYSQL_RES *res = db.executeQuery(query);
	int resultsAmount = 0;
	while (row = mysql_fetch_row(res))
	{
		resultsAmount++;
		OrderState orderState = (OrderState)atoi(row[4]);

		std::cout << "\tID: " << row[0];

		std::cout << "\n\tOrder status: ";

		switch (orderState) {
		case Ordered:
			std::cout << "Ordered";
			break;
		case Confirmed:
			std::cout << "Confirmed";
			break;
		}

		std::cout << std::endl;
	}
	if (resultsAmount == 0) {
		std::cout << "\tThere aren't orders of this patient" << std::endl;
	}
}

Order Order::getOrder(int id, DbConnector &db)
{
	std::string query = "SELECT * FROM `Order` WHERE `Order_ID`=" + std::to_string(id);
	MYSQL_ROW row;
	MYSQL_RES *res = db.executeQuery(query);
	if (row = mysql_fetch_row(res))
	{
		return Order(atoi(row[0]), atoi(row[1]), (OrderState)atoi(row[2]));
	}
	return Order(-1, -1, (OrderState)0);
}


ModificationResult Order::confirmOrder(int id, DbConnector &db)
{
	Order tmpOrder = getOrder(id, db);


	if (tmpOrder.getId() != -1) {

		std::string query = "UPDATE `Order` SET `Order_state`=" + std::to_string(1) + " WHERE `Order_ID`=" + std::to_string(id);
		db.executeQuery(query);
		return ModificationResult::Successed;
	}

	return ModificationResult::Failed;

}


ModificationResult Order::addOrder(int userId, DbConnector &db) {
	std::string query = "INSERT INTO Order(User_ID_FK, Order_state) Values(\'"
		+ std::to_string(userId)
		+ ", " + std::to_string(0)
		+ ")";
	db.executeQuery(query);
	if (db.getQueryState() == DbConnector::QueryState::Successed) {
		return ModificationResult::Successed;
	}
	return ModificationResult::Failed;
}

