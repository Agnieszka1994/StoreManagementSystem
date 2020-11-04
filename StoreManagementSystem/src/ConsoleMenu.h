#pragma once
#include <sqlite_orm.h>
#include <iostream>
#include "StorageMacro.h"
#include <iomanip>

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


class ConsoleMenu
{
	StorageType _storage = sqlite_orm::make_storage("test_db.sqlite",
		sqlite_orm::make_table("users",
			sqlite_orm::make_column("id", &User::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
			sqlite_orm::make_column("type_id", &User::typeId),
			sqlite_orm::make_column("login", &User::login),
			sqlite_orm::make_column("password", &User::password)),
		sqlite_orm::make_table("products",
			sqlite_orm::make_column("id", &Product::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
			sqlite_orm::make_column("name", &Product::name),
			sqlite_orm::make_column("price", &Product::price),
			sqlite_orm::make_column("quantity", &Product::quantity)),
		sqlite_orm::make_table("orders",
			sqlite_orm::make_column("id", &Order::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
			sqlite_orm::make_column("userId", &Order::userId),
			sqlite_orm::make_column("productId", &Order::productId),
			sqlite_orm::make_column("quantity", &Order::quantity),
			sqlite_orm::make_column("status", &Order::status)),
		sqlite_orm::make_table("user_types",
			sqlite_orm::make_column("id", &UserType::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
			sqlite_orm::make_column("name", &UserType::name, sqlite_orm::default_value("user"))));

	bool running;
	int userTypeLogged;
	int userIDLogged;
	User _insertCustomer(std::string name);
	Product _insertProduct(std::string name, double price, int quantity);
	Order _insertOrder(int id, int userId, int productId, int quantity, std::string status);
	void _displayUserHeader();
	void _displayAdminHeader();
	void _displayStockHeader();
	void _displayUserStatsHeader();

	template<typename T>
	void displayOrdersAdmin(T sqlQuery);
	template<typename T>
	void displayOrdersUser(T sqlQuery);
	template<typename T>
	void displayProducts(T sqlQuery);
	template<typename T>
	void displayUsers(T sqlQuery);

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
	void checkOrderById();
	void displayAllOrdersUser();
	void deleteUserAccount();
	
	// admin option
	void displayStock();
	void addProduct();
	void deleteProduct();
	void cancelOrder();
	void displayAllOrdersAdmin();
	void displayActiveOrdersAdmin();
	void completeOrder();
	void changeProductQty();
	void displayUsersStatistic();	
};

template<typename T>
inline void ConsoleMenu::displayOrdersAdmin(T sqlQuery)
{
	for (auto& order : sqlQuery) {
		std::cout << std::setw(9) << std::left << std::get<0>(order)
			<< std::setw(8) << std::left << std::get<1>(order)
			<< std::setw(15) << std::left << std::get<2>(order)
			<< std::setw(15) << std::left << std::get<3>(order)
			<< std::setw(11) << std::left << std::get<4>(order)
			<< std::setw(11) << std::left << std::get<5>(order)
			<< std::setw(11) << std::left << std::fixed << std::setprecision(2)
			<< std::get<6>(order)
			<< std::setw(11) << std::left << std::fixed << std::setprecision(2)
			<< (double)std::get<5>(order) * (double)std::get<6>(order)
			<< std::setw(11) << std::right << std::get<7>(order)
			<< std::endl;
	}
}

template<typename T>
inline void ConsoleMenu::displayOrdersUser(T sqlQuery)
{
	for (auto& order : sqlQuery) {
		std::cout << std::setw(9) << std::left << std::get<0>(order)
			<< std::setw(15) << std::left << std::get<1>(order)
			<< std::setw(11) << std::left << std::get<2>(order)
			<< std::setw(11) << std::left << std::get<3>(order)
			<< std::setw(11) << std::left << std::fixed << std::setprecision(2)
			<< std::get<4>(order)
			<< std::setw(11) << std::left << std::fixed << std::setprecision(2)
			<< (double)std::get<3>(order) * (double)std::get<4>(order)
			<< std::setw(11) << std::left << std::get<5>(order)
			<< std::endl;
	}
}

template<typename T>
inline void ConsoleMenu::displayProducts(T sqlQuery)
{
	for (auto& product : sqlQuery) {
		//std::cout << _storage.dump(product) << std::endl;
		std::cout << std::setw(4) << std::left << product.id
			<< std::setw(15) << std::left << product.name
			<< std::setw(10) << std::left << std::fixed << std::setprecision(2) << product.price
			<< std::setw(10) << std::right << product.quantity
			<< std::endl;
	}
}

template<typename T>
inline void ConsoleMenu::displayUsers(T sqlQuery)
{
	for (auto& user : sqlQuery) {
		std::cout << std::setw(9) << std::left << std::get<0>(user)
			<< std::setw(15) << std::left << std::get<1>(user)
			<< std::setw(11) << std::left << std::get<2>(user)
			<< std::setw(11) << std::left << std::get<3>(user)
			<< std::setw(11) << std::left << std::fixed << std::setprecision(2)
			<< (double)std::get<3>(user) * (double)std::get<4>(user)
			<< std::endl;
	}
}
