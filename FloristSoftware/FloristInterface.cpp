#include "pch.h"
#include "FloristInterface.h"


auto basketAmount = [](std::vector<Product> &tmpBasket) {
	double amount = 0;
	for (Product &product : tmpBasket) {
		amount += product._price;
	}
	return amount;
};


FloristInterface::FloristInterface(DbConnector &db) : _db(db)
{
}


FloristInterface::~FloristInterface()
{
}


bool FloristInterface::addProductToBasket() {

	int productId = -1, amount = -1;

	showProducts();

	std::cout << "\n\tType in id of product to add to basket: ";

	std::cin >> productId;

	if (std::cin.fail()) {
		std::cout << "\n\tNo way!\n";
		return false;
	}

	if (productId < 0 || productId >= _products.size()) {
		std::cout << "\n\tWrong product!\n";
		return false;
	}

	/*std::cout << "\n\tType in amount of this product: ";

	std::cin >> amount;

	if (std::cin.fail()) {
		std::cout << "\n\tNo way!\n";
		return false;
	}

	if (amount <= 0) {
		std::cout << "\n\tWrong amount!\n";
		return false;
	}*/

	_basket.push_back(_products.at(productId));

	std::cout << "\n\tProduct added to basket\n";

	return true;
}

bool FloristInterface::addOrder(int userID) {


	std::string query = "INSERT INTO `Order`(`User_ID_FK`, `Order_state`) Values("
		+ std::to_string(userID)
		+ ", " + std::to_string(0)
		+ ")";
	_db.executeQuery(query);
	if (_db.getQueryState() == DbConnector::QueryState::Successed) {


		query = "SELECT LAST_INSERT_ID()";
		MYSQL_ROW row;
		MYSQL_RES *res = _db.executeQuery(query);
		if (_db.getQueryState() != DbConnector::QueryState::Successed) {
			_basket.clear();
			return false;
		}

		if (row = mysql_fetch_row(res))
		{
			int orderID = atoi(row[0]);


			for (Product &product : _basket) {
				query = "INSERT INTO OrderPos(OrderPos_OrderID, OrderPos_ProdID, OrderPos_Price) Values("
					+ std::to_string(orderID)
					+ ", " + std::to_string(product._id)
					+ ", " + std::to_string(product._price)
					+ ")";
				_db.executeQuery(query);
			}

			std::cout << "\n\tOrder waits to be confirmed\n";

			_basket.clear();
			return true;
		}
		else {
			_basket.clear();
			return false;
		}
	}
	else {
		_basket.clear();
		return false;
	}
}

void FloristInterface::showBasket(int userID) {

	if (_basket.empty()) {
		std::cout << "\n\tYou basket is empty!\n";
	}
	else {

		std::sort(_basket.begin(), _basket.end(), [](const Product comparedProduct1, const Product comparedProduct2){
			return comparedProduct2._price < comparedProduct1._price;
		});

		std::cout << "\n\tProducts in your basket:\n";

		for (Product &product : _basket) {
			std::cout << "\n\t" << product._name << ", Price: " << product._price;
		}

		std::cout << "\n\t\tTotal amount: " << basketAmount(_basket) << std::endl;

		int option = -1;

		std::cout << "\n\tDo you want to finish order? ( 1 - YES, 0 - NO): ";

		std::cin >> option;

		if(option == 1)
			addOrder(userID);
	}

}


void FloristInterface::showOrdersHistory(int userID) {

	std::string query = "SELECT * FROM `Order` WHERE `User_ID_FK`=" + std::to_string(userID) + " ORDER BY `Order_state`";
	std::cout << query << std::endl;
	MYSQL_ROW row;
	MYSQL_RES *res = _db.executeQuery(query);
	int resultsAmount = 0;
	while (row = mysql_fetch_row(res))
	{
		resultsAmount++;

		Order::OrderState orderState = (Order::OrderState)atoi(row[2]);

		std::cout << "\tID: " << row[0];

		std::cout << "\n\tOrder status: ";

		switch (orderState) {
		case Order::OrderState::Ordered:
			std::cout << "Ordered";
			break;
		case Order::OrderState::Confirmed:
			std::cout << "Confirmed";
			break;
		}

		showOrderPositions(atoi(row[0]), _db);

		std::cout << std::endl;
	}
	if (resultsAmount == 0) {
		std::cout << "\tThere aren't orders of this user" << std::endl;
	}
}

void FloristInterface::showOrderPositions(int orderId, DbConnector &db) {
	std::string query = "SELECT * FROM OrderPos WHERE OrderPos_OrderID=" + std::to_string(orderId);
	MYSQL_ROW row;
	MYSQL_RES *res = db.executeQuery(query);
	while (row = mysql_fetch_row(res))
	{
		
		Product tmpProduct = _products.at(atoi(row[2]));

		std::cout << "\n\t\t" << tmpProduct._name << ", Price: " << tmpProduct._price;
	}
}

void FloristInterface::showProducts() {

	std::cout << "\n\tCurrently avaiable products:\n";

	int index = 0;

	for (Product &product : _products) {
		std::cout << "\n\t" << index << ". " <<  product._name << ", Price: " << product._price;
		++index;
	}
}


bool FloristInterface::confirmOrder(int orderId) {
	
	if (Order::getOrder(orderId, _db).getId() == -1) {
		std::cout << "\n\tError!";
		return false;
	}

	if (Order::confirmOrder(orderId, _db) == ModificationResult::Failed) {
		std::cout << "\n\tError!";
		return false;
	}
	else {
		std::cout << "\n\tOrder confirmed.";
		return true;
	}
}


bool FloristInterface::addUser(std::string email, std::string password) {

	if (!std::regex_match(email, std::regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"))) {
		std::cout << "\n\tWrong email format!\n";
		return false;
	}

	if (User::addUser(email, password, _db) == ModificationResult::Failed) {
		std::cout << "\n\tCustomer account added.\n";
		return true;
	}
	else {
		std::cout << "\n\tError occured.\n";
		return false;
	}

	return true;
}