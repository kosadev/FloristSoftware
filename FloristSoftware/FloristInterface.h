#pragma once
#include "pch.h"
#include "DbConnector.h"
#include "Order.h"
#include "User.h"


class FloristInterface
{
public:
	FloristInterface(DbConnector &db);
	~FloristInterface();


	DbConnector _db;
};

