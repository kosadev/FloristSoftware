#include "DbConnector.h"

#include "pch.h"
#include "DbConnector.h"

DbConnector::DbConnector() {

}

DbConnector::DbConnector(dbStr serverName, dbStr userName, dbStr dbPassword, dbStr dbName) :
	_serverName(serverName),
	_userName(userName),
	_dbPassword(dbPassword),
	_dbName(dbName)
{
	_conn = mysql_init(0);
}


DbConnector::QueryState DbConnector::connect() {

	_conn = mysql_real_connect(_conn, (char*)_serverName, (char*)_userName, (char*)_dbPassword, (char*)_dbName, 3306, NULL, 0);

	if (_conn) {
		puts("Connected to database!");
		_queryState = DbConnector::QueryState::Successed;
		return _queryState;
	}
	else {
		puts("Database connectin error!");
		_queryState = DbConnector::QueryState::ConnectionError;
		return _queryState;
	}
}


DbConnector::QueryState DbConnector::getQueryState() {
	return _queryState;
}





MYSQL_RES* DbConnector::executeQuery(std::string query) {
	const char* q = query.c_str();
	_queryState = DbConnector::QueryState(mysql_query(_conn, q));
	if (!_queryState)
	{
		MYSQL_RES *res = mysql_store_result(_conn);
		return res;
	}
	else
	{
		std::cout << "Query failed: " << mysql_error(_conn) << std::endl;
		return nullptr;
	}
}


int DbConnector::countRecords(std::string table) {

	std::string query = "SELECT COUNT(*) FROM " + table;
	executeQuery(query);
	MYSQL_ROW row;
	MYSQL_RES *res = executeQuery(query);
	if (row = mysql_fetch_row(res)) {
		return atoi(row[0]);
	}
	return -1;
}

DbConnector::~DbConnector()
{
}
