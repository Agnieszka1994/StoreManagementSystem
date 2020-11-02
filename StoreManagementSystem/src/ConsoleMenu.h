#pragma once
#include "DBLite.h"

class ConsoleMenu
{
	bool running;
	int userTypeLogged;

public:
	ConsoleMenu();
	void run();
	void showMain();
	void showUser();
	void showAdmin();
	void logIn();
	void createCustomerAccount();
	void insertProduct(std::string name, float price, int quantity);
	void insertCustomer(std::string firstName);
};


