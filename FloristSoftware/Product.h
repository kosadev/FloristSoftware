#pragma once
#include "pch.h"
#include "DbConnector.h"

class Product
{
public:
	Product(int id, std::string name, double price);
	~Product();

	int _id;
	std::string _name;
	double _price;
};

