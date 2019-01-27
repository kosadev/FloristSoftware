#include "pch.h"
#include "Product.h"


Product::Product(int id, std::string name, double price) :
	_id(id),
	_name(name),
	_price(price)
{
}


Product::~Product()
{
}
