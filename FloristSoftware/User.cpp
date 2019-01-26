#include "pch.h"
#include "User.h"


uint32_t shortcode(std::string const & s)
{
	uint32_t hash = 5381;
	for (auto c : s) {
		hash = (hash << 5) + hash + c;
	}
	return hash;
}



User::User() :
	_id(-1),
	_login(""),
	_password(""),
	_isEmployee(0),
	_isConfirmed(0)
{

}

User::User(int id, std::string login, std::string password, int isEmployee, int isConfirmed) :
	_id(id),
	_login(login),
	_password(password),
	_isEmployee(isEmployee),
	_isConfirmed(isConfirmed)
{
}


User::~User()
{
}

User User::login(std::string login, std::string password, DbConnector &db) {
	std::string query = "SELECT * FROM User WHERE User_Name='" + login + "' AND User_Password='" + std::to_string(shortcode(password)) + "'";
	std::cout << query << std::endl;
	MYSQL_ROW row;
	MYSQL_RES *res = db.executeQuery(query);
	if (row = mysql_fetch_row(res))
	{
		return User(atoi(row[0]), row[1], row[2], atoi(row[3]), atoi(row[4]));
	}
	return User(-1, "", "", 0, 0);
}

User User::logout() {

	this->_id = -1;
	this->_login = "";
	this->_password = "";
	this->_isEmployee = 0;
	this->_isConfirmed = 0;
	return User(-1, "", "", 0, 0);
}

int User::getId() {
	return _id;
}

std::string User::getLogin() {
	return _login;
}

User User::getUser(int id, DbConnector &db) {
	std::string query = "SELECT * FROM User WHERE User_ID=" + std::to_string(id);
	MYSQL_ROW row;
	MYSQL_RES *res = db.executeQuery(query);
	if (row = mysql_fetch_row(res))
	{
		return User(atoi(row[0]), row[1], row[2], atoi(row[3]), atoi(row[4]));
	}
	return User(-1, "", "", 0, 0);
}


int User::isEmployee() {
	return _isEmployee;
}


int User::isConfirmed() {
	return _isConfirmed;
}

int User::countUsersByEmail(std::string email, DbConnector &db) {
	return db.countRecords("User WHERE User_Name=" + email);
}


ModificationResult User::addUser(std::string name, std::string password, DbConnector &db) {

	if (countUsersByEmail(name, db) == 0) {
		std::string query = "INSERT INTO User(User_Name, User_Password, User_isAdmin, User_isConfirmed) Values(\'"
			+ name + "\',\'"
			+ std::to_string(shortcode(password)) + "\',"
			+ std::to_string(0) + ","
			+ std::to_string(0) + ")";


		db.executeQuery(query);
		if (db.getQueryState() == DbConnector::QueryState::Successed) {
			return ModificationResult::Successed;
		}
	}

	return ModificationResult::Failed;
}