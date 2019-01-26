#ifndef USER_H
#define USER_H


#pragma once
#include "pch.h"
#include "DbConnector.h"


class User
{
public:
	User();

	User(int id, std::string login, std::string password, int isEmployee, int isConfirmed);
	~User();

	static User login(std::string login, std::string password, DbConnector &db);
	User logout();

	static ModificationResult addUser(std::string name, std::string password, DbConnector &db);
	static ModificationResult changeUserPassword(std::string name, std::string password, DbConnector &db);
	static int countUsersByEmail(std::string email, DbConnector &db);

	int getId();
	std::string getLogin();
	int isEmployee();
	int isConfirmed();

	static User getUser(int id, DbConnector &db);

private:
	int _id;
	std::string _login;
	std::string _password;
	int _isEmployee;
	int _isConfirmed;
};



#endif // User_H
