#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H


#pragma once
#include "pch.h"

class DbConnector
{
public:

	enum QueryState {
		Successed,
		ImproperOrderCommand,
		ServerError,
		ConnectionError,
		UnknownError
	};

	DbConnector();
	DbConnector(dbStr serverName, dbStr userName, dbStr dbPassword, dbStr dbName);
	~DbConnector();

	QueryState connect();
	QueryState getQueryState();

	MYSQL_RES* executeQuery(std::string query);
	int countRecords(std::string table);

	friend void showServerInfo(DbConnector &db) {
		std::cout << "\tServer information:\n"
			<< "\t\tServer name: " << db._serverName
			<< "\n\t\tDatabase name:  " << db._dbName
			<< "\n\n";
	}

private:
	dbStr _serverName;
	dbStr _userName;
	dbStr _dbPassword;
	dbStr _dbName;

	QueryState _queryState = QueryState::UnknownError;
	MYSQL* _conn;

};



#endif // DBCONNECTOR_H
