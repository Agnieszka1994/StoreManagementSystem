#include "ConsoleMenu.h"
#include "PassGenerator.h"
#include <iomanip>

using namespace sqlite_orm;
ConsoleMenu::ConsoleMenu()
{
	_storage.sync_schema();
	running = true;
	userTypeLogged = 1;
	userIDLogged = 0;
	User admin = { 0, 1, "ADMIN", "ADMIN" };
	_storage.replace(admin);
}

void ConsoleMenu::run()
{
	int choice;
	while (running) {
		while (userTypeLogged == NULL) {
			system("cls");
			this->showMain();
			std::cin >> choice;
			switch (choice) {
			case 1:
				logIn();
				system("pause");
				break;
			case 2:
				createCustomerAccount();
				system("pause");
				break;
			case 0:
				exit(0);
				break;
			}
		}
		while (userTypeLogged == 1) {
			system("cls");
			this->showAdmin();
			std::cin >> choice;
			switch (choice) {
			case 1:
				addProduct();
				system("pause");
				break;
			case 5:
				displayStock();
				system("pause");
				break;
			case 6:
				deleteProduct();
				system("pause");
				break;
			case 0:
				exit(0);
				break;
			}
			
		}
		while (userTypeLogged == 2) {
			system("cls");
			this->showUser();
			std::cin >> choice;
			
		}
	}
}

void ConsoleMenu::showMain()
{
	std::cout << "1. Log in" << std::endl;
	std::cout << "2. Create Account" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

void ConsoleMenu::showUser()
{
	std::cout << "1. Place Order" << std::endl;
	std::cout << "2. Check order" << std::endl;
	std::cout << "3. Show all orders" << std::endl;
	std::cout << "4. Delete account" << std::endl; //check if active orders exist
	std::cout << "0. Log out" << std::endl;
}

void ConsoleMenu::showAdmin()
{
	std::cout << "1. Add products" << std::endl;
	std::cout << "2. Change product" << std::endl;
	std::cout << "3. Display all orders" << std::endl;
	std::cout << "4. Complete order" << std::endl; 
	std::cout << "5. Display stock" << std::endl;
	std::cout << "6. Delete product from stock" << std::endl;
	std::cout << "0. Log out" << std::endl;
}

void ConsoleMenu::logIn()
{
	int id;
	std::string password;
	std::cout << "Please enter your ID:" << std::endl;
	std::cin >> id;
	std::cout << "Please enter your password:" << std::endl;
	std::cin >> password;
	if (auto user = _storage.get_pointer<User>(id)) {
		if (user->password == password) {
			userTypeLogged = user->typeId;
			userIDLogged = user->id;
			std::cout << "Succesfully logged: " << user->id << " " << user->login << std::endl;
			return;
		}
		else {
			std::cout << "Wrong password!" << id << std::endl;
			return;
		}	
	}
	else {
		std::cout << "No user with id " << id << std::endl;
		std::cout << "Please try again" << std::endl;
		return;
	}
}

void ConsoleMenu::logOut()
{
	userTypeLogged = NULL;
	userIDLogged = NULL;
	std::cout << "Succesfully logged out." << std::endl;
	return;
}


Product ConsoleMenu::_insertProduct(std::string name, double price, int quantity)
{
	Product new_product = { -1, name, price, quantity};
	new_product.id = _storage.insert(new_product); // insert returns inserted id
	return new_product;
}

void ConsoleMenu::addProduct()
{
	std::string product_name;
	double price;
	std::cout << "Please enter product name:" << std::endl;
	std::cin >> product_name;
	std::cout << "Please enter product price:" << std::endl;
	std::cin >> price;
	if (!price or product_name == "") {
		std::cout << "Missing product name or price!" << std::endl;
		return;
	}
	else {
		Product new_product = _insertProduct(product_name, price, 0);
		std::cout << "New product has been added:" << std::endl;
		std::cout << "ID: " << new_product.id << std::endl;
		std::cout << "Name: " << new_product.name << std::endl;
		std::cout << "Price: " << new_product.price << std::endl;
		return;
	}
}

void ConsoleMenu::deleteProduct()
{
	displayStock();
	int id;
	std::cout << "Please enter product ID:" << std::endl;
	std::cin >> id;
	if (auto product = _storage.get_pointer<Product>(id)) {
		char choice;
		std::cout << "Are you sure to delete Product: " << product->name << " from stock? Y/N" << std::endl;
		std::cin >> choice;
		if (choice == 'Y') {
			_storage.remove<Product>(id);
			std::cout << "Product: " << id << " " << product->name << " deleted from stock." << std::endl;
			return;
		}
		else {
			return;
		}
	}
	else {
		std::cout << "No product with id " << id << std::endl;
		std::cout << "Please try again" << std::endl;
		return;
	}
}

User ConsoleMenu::_insertCustomer(std::string name)
{
	User new_user = { -1, 2, name, random_string(8) };
	new_user.id = _storage.insert(new_user); //  insert returns inserted id
	return new_user;	
}
void ConsoleMenu::createCustomerAccount()
{
	std::string user_name;
	std::cout << "Please enter your name:" << std::endl;
	std::cin >> user_name;
	User new_user = _insertCustomer(user_name);
	std::cout << "Account has been created!" << std::endl;
	std::cout << "Your ID: " << new_user.id << std::endl;
	std::cout << "Your login: " << new_user.login << std::endl;
	std::cout << "Password: " << new_user.password << std::endl;
}

void ConsoleMenu::displayStock()
{
	auto products = _storage.get_all<Product>(order_by(&Product::id));
	std::cout << products.size() << "products available in stock:" << std::endl;
	std::cout << std::setw(4) << std::left << "ID" 
			<< std::setw(15) << std::left << "NAME"
			<< std::setw(15) << std::left << "PRICE"
			<< std::setw(10) << std::right << "QUANTITY"
			<< std::endl;
	for (auto& product : products) {
		
		//std::cout << _storage.dump(product) << std::endl;
		std::cout << std::setw(4) << std::left << product.id 
				<< std::setw(15) << std::left << product.name 
				<< std::setw(15) << std::left << std::fixed << std::setprecision(2) << product.price
				<< std::setw(10) << std::right << product.quantity 
				<< std::endl;
	}
}


