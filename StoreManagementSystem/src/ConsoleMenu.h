#pragma once
#include <sqlite_orm.h>
#include <iostream>
#include "StorageMacro.h"

struct User {
	int id=0;
	int typeId;
	std::string login="";
	std::string password;
};

struct UserType {
	int id;
	std::string name;
};

struct Product {
	int id;
	std::string name;
	double price;
	int quantity;
};

struct Order {
	int id;
	int userId;
	int productId;
	int quantity;
	std::string status;
};

using namespace sqlite_orm;
class ConsoleMenu
{
	StorageType _storage = make_storage("test_db.sqlite",
		make_table("users",
			make_column("id", &User::id, autoincrement(), primary_key()),
			make_column("type_id", &User::typeId),
			make_column("login", &User::login),
			make_column("password", &User::password)),
		make_table("products",
			make_column("id", &Product::id, autoincrement(), primary_key()),
			make_column("name", &Product::name),
			make_column("price", &Product::price),
			make_column("quantity", &Product::quantity)),
		make_table("orders",
			make_column("id", &Order::id, autoincrement(), primary_key()),
			make_column("userId", &Order::userId),
			make_column("productId", &Order::productId),
			make_column("quantity", &Order::quantity),
			make_column("status", &Order::status)),
		make_table("user_types",
			make_column("id", &UserType::id, autoincrement(), primary_key()),
			make_column("name", &UserType::name, default_value("user"))));

	bool running;
	int userTypeLogged;
	int userIDLogged;
	User _insertCustomer(std::string name);
	Product _insertProduct(std::string name, double price, int quantity);
	Order _insertOrder(int id, int userId, int productId, int quantity, std::string status);

public:
	ConsoleMenu();
	void run();
	void showMain();
	void showUser();
	void showAdmin();
	// user option
	void logIn();
	void logOut();
	void createCustomerAccount();
	void placeOrder();
	void displayAllOrdersUser();
	
	// admin option
	void displayStock();
	void addProduct();
	void deleteProduct();
	void changeProduct();
	void displayAllOrdersAdmin();
	void completeOrder();
	void changeProductQty();
	
	
};


