// FloristSoftware.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "User.h"
#include "FloristInterface.h"

void serveLoginMenu(DbConnector &db, SelectedOption &sOption);
void serveAdminMenu(SelectedOption &sOption);
void serveMenu(SelectedOption &sOption);
void serveProducts(SelectedOption &sOption);

User user(-1, "", "", -1, -1);
FloristInterface *floristInterface = nullptr;

int main()
{
	DbConnector database((dbStr)"serwer1803050.home.pl", (dbStr)"27637716_fs", (dbStr)"HaloPolicja997", (dbStr)"27637716_fs");

	DbConnector::QueryState connectionState = database.connect();

	system("cls");
	std::cout << "Welcome to the Poverty Florist Soft!\n\n";

	if (connectionState != DbConnector::QueryState::Successed) {
		std::cout << "\n\tError: Database connection error: " << connectionState << "\n";
		return 1;
	}

	SelectedOption selectedOption = SelectedOption::NoOption;

	floristInterface = new FloristInterface(database);

	while (selectedOption != SelectedOption::Exit) {

		if (user.isEmployee() == 1) {
			serveAdminMenu(selectedOption);
		}
		else if (user.getId() != -1) {
			serveMenu(selectedOption);
		}
		else {
			serveLoginMenu(database, selectedOption);
		}

		std::cout << "\n";
		system("pause");
		system("cls");
		std::cout << "Welcome to the Poverty Florist Soft!\n\n";
	}


	printf("\n\n\n\n");
	return 0;

}



void serveLoginMenu(DbConnector &db, SelectedOption &sOption) {
	std::cout << "Select option you want\n";
	std::cout
		<< " 1. Login.\n"
		<< " 2. Exit.\n";
	std::cout << "  Type in your option: ";

	int option = 0;

	std::cin >> option;


	if (std::cin.fail()) {
		sOption = SelectedOption::NoOption;
		option = -1;
		return;
	}

	switch (option) {
	case 1:
		sOption = SelectedOption::Login;
		break;
	case 2:
		std::cout << "\tHasta la vista baby!\n";
		sOption = SelectedOption::Exit;
		break;
	default:
		std::cout << "\t Wrong option typed in\n";
		sOption = SelectedOption::NoOption;
		break;
	}

	if (sOption == SelectedOption::Login) {
		system("cls");
		std::cout << "Welcome to the Poverty Florist Soft!\n\n";
		std::cout << " Log in process\n"
			<< "  Your login: ";

		std::string login = "", password = "";

		std::cin >> login;

		std::cout << "  Your password: ";

		std::cin >> password;

		user = User::login(login, password, db);

		if (user.getId() == -1) {
			std::cout << "\tLogin proccess failed\n";
			sOption = SelectedOption::NoOption;
		}
		else if (user.isConfirmed() == 0) {
			std::cout << "\tUser account is not confirmed\n";
			sOption = SelectedOption::NoOption;
		}
		else {
			std::cout << "\tLogin proccess successed\n";
		}
	}
}

void serveMenu(SelectedOption &sOption) {
	std::cout << "Select module you want\n";
	std::cout
		<< " 1. Add product to basket.\n"
		<< " 2. Basket.\n"
		<< " 3. Show orders history.\n"
		<< " 4. Logout.\n"
		<< " 5. Exit.\n";


	std::cout << "  Type in your option: ";

	int option = 0;

	std::cin >> option;

	if (std::cin.fail()) {
		sOption = SelectedOption::NoOption;
		option = -1;
	}


	switch (option) {
	case 1:
		floristInterface->addProductToBasket();
		break;
	case 2:
		floristInterface->showBasket(user.getId());
		break;
	case 3:
		floristInterface->showOrdersHistory(user.getId());
		break;
	case 4:
		user.logout();
		sOption = SelectedOption::NoOption;
		break;
	case 5:
		std::cout << "\tHasta la vista baby!\n";
		sOption = SelectedOption::Exit;
		break;
	default:
		std::cout << "\t Wrong option typed in\n";
		sOption = SelectedOption::NoOption;
		break;
	}
}

void serveAdminMenu(SelectedOption &sOption) {
	std::cout << "\n\newsddsf\n";
}


void serveProducts(SelectedOption &sOption) {

}