#include "ConsoleMenu.h"
#include "PassGenerator.h"
#include "InputHandler.h"
#include <iomanip>

void noOption() {
	std::cout << "No such option!" << std::endl;
}

using namespace sqlite_orm;
ConsoleMenu::ConsoleMenu()
{
	_storage.sync_schema();
	running = true;
	userTypeLogged = NULL;
	userIDLogged = NULL;
	User admin = { 0, 1, "ADMIN", "ADMIN" };
	_storage.replace(admin);
}

void ConsoleMenu::run()
{	
	while (running) {
		while (userTypeLogged == NULL) {
			system("cls");
			this->showMain();
			int choice = getChoice<int>();
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
			default:
				noOption();
				break;
			}
		}
		while (userTypeLogged == 1) {
			system("cls");
			this->showAdmin();
			int choice = getChoice<int>();
			switch (choice) {
			case 1:
				addProduct();
				system("pause");
				break;
			case 2:
				changeProduct();
				system("pause");
				break;
			case 3:
				displayAllOrdersAdmin();
				system("pause");
				break;
			case 4:
				completeOrder();
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
			case 7:
				changeProductQty();
				system("pause");
				break;
			case 0:
				logOut();
				break;
			default:
				noOption();
				break;
			}
			
		}
		while (userTypeLogged == 2) {
			system("cls");
			this->showUser();
			int choice = getChoice<int>();
			switch (choice) {
			case 1:
				placeOrder();
				system("pause");
				break;
			case 2:
				system("pause");
				break;
			case 3:
				displayAllOrdersUser();
				system("pause");
				break;
			case 0:
				logOut();
				break;
			default:
				noOption();
				break;
			}
			
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
	std::cout << "3. Display all orders" << std::endl;
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
	std::cout << "7. Add or subtract qty from stock" << std::endl;
	std::cout << "0. Log out" << std::endl;
}

void ConsoleMenu::logIn()
{
	std::cout << "Please enter your ID:" << std::endl;
	int id = getChoice<int>();
	std::cout << "Please enter your password:" << std::endl;
	std::string password = getChoice<std::string>();
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

User ConsoleMenu::_insertCustomer(std::string name)
{
	User new_user = { -1, 2, name, random_string(8) };
	new_user.id = _storage.insert(new_user); //  insert returns inserted id
	return new_user;
}

Product ConsoleMenu::_insertProduct(std::string name, double price, int quantity)
{
	Product new_product = { -1, name, price, quantity};
	new_product.id = _storage.insert(new_product); // insert returns inserted id
	return new_product;
}

Order ConsoleMenu::_insertOrder(int id, int userId, int productId, int quantity, std::string status)
{
	Order new_order = { -1, userId, productId, quantity, status};
	new_order.id = _storage.insert(new_order); // insert returns inserted id
	return new_order;
}

void ConsoleMenu::addProduct()
{
	std::cout << "Please enter product name:" << std::endl;
	std::string product_name = getChoice<std::string>();
	std::cout << "Please enter product price:" << std::endl;
	double price = getChoice<double>();
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
	std::cout << "Please enter product ID:" << std::endl;
	int id = getChoice<int>();
	if (auto product = _storage.get_pointer<Product>(id)) {
		std::cout << "Are you sure to delete Product: " << product->name << " from stock? Y/N" << std::endl;
		char choice = getChoice<char>();
		if (choice == 'Y') {
			_storage.remove<Product>(id);
			std::cout << "Product: " << id << " " << product->name << " deleted from stock." << std::endl;
			return;
		}
		else {
			std::cout << "Product has NOT beed deleted." << id << std::endl;
			return;
		}
	}
	else {
		std::cout << "No product with id " << id << std::endl;
		std::cout << "Please try again" << std::endl;
		return;
	}
}

void ConsoleMenu::changeProduct()
{
}

void ConsoleMenu::displayAllOrdersAdmin()
{
}

void ConsoleMenu::completeOrder()
{
}

void ConsoleMenu::changeProductQty()
{
	displayStock();
	std::cout << "Please enter product ID:" << std::endl;
	int id = getChoice<int>();
	if (auto product = _storage.get_pointer<Product>(id)) {
		std::cout << "Current qty: " << product->quantity << "; product: " << product->name << std::endl;
		std::cout << "Enter New quantity: " << std::endl;
		int quantity = getChoice<int>();
		if (quantity > 0) {
			product->quantity = quantity;
			_storage.update(*product);
			std::cout << "Quantity opdated: " << product->quantity << std::endl;
			return;
		}
		else {
			std::cout << "Wrong quantity!" << std::endl;
			return;
		}
	}
	else {
		std::cout << "No product with id " << id << std::endl;
		std::cout << "Please try again" << std::endl;
		return;
	}
}

void ConsoleMenu::createCustomerAccount()
{
	std::cout << "Please enter your name:" << std::endl;
	std::string user_name = getChoice<std::string>();
	User new_user = _insertCustomer(user_name);
	std::cout << "Account has been created!" << std::endl;
	std::cout << "Your ID: " << new_user.id << std::endl;
	std::cout << "Your login: " << new_user.login << std::endl;
	std::cout << "Password: " << new_user.password << std::endl;
}

void ConsoleMenu::placeOrder()
{
	displayStock();
	std::cout << "Please enter product ID:" << std::endl;
	int id = getChoice<int>();
	if (auto product = _storage.get_pointer<Product>(id)) {
		std::cout << "Enter quantity: " << std::endl;
		int quantity = getChoice<int>();
		if (quantity <= product->quantity) {
			Order new_order = _insertOrder(-1, userIDLogged, product->id, quantity, "new");
			std::cout << "Order: " << id << " created." << std::endl;
			return;
		}
		else {
			std::cout << "Quantity insufficient!" << std::endl;
			return;
		}
	}
	else {
		std::cout << "No product with id " << id << std::endl;
		std::cout << "Please try again" << std::endl;
		return;
	}
}

void ConsoleMenu::displayAllOrdersUser()
{
	auto ordersByUserId = _storage.get_all<Order>(where(c(&Order::userId) == userIDLogged));
	if (ordersByUserId.size() == 0) {
		std::cout << "No orders found" << std::endl;
	}
	else {
		auto ordersDetails = _storage.select(columns(&Order::id, &Product::name, &Product::id, &Order::quantity, &Product::price),
			inner_join<Product>(on(c(&Product::id) == &Order::productId)),
			where(c(&Order::userId) == userIDLogged));
		std::cout << std::setw(9) << std::left << "Order ID"
			<< std::setw(15) << std::left << "PROD. NAME"
			<< std::setw(11) << std::left << "PROD. ID"
			<< std::setw(11) << std::left << "ORDER QTY"
			<< std::setw(11) << std::left << "UNIT PRICE"
			<< std::setw(11) << std::right << "TOTAL PRICE"
			<< std::endl;
		for (auto& order : ordersDetails) {
			std::cout << std::setw(9) << std::left << std::get<0>(order)
				<< std::setw(15) << std::left << std::get<1>(order) 
				<< std::setw(11) << std::left << std::get<2>(order)
				<< std::setw(11) << std::left << std::get<3>(order)
				<< std::setw(11) << std::left << std::fixed << std::setprecision(2)
				<< std::get<4>(order)
				<< std::setw(11) << std::left << std::fixed << std::setprecision(2) 
				<< (double)std::get<3>(order) * (double)std::get<4>(order)
				<< std::endl;
		}
	}
}

void ConsoleMenu::displayStock()
{
	auto products = _storage.get_all<Product>(order_by(&Product::id));
	std::cout << std::endl << products.size() << " products available in stock:" << std::endl << std::endl;
	std::cout << std::setw(4) << std::left << "ID" 
			<< std::setw(15) << std::left << "NAME"
			<< std::setw(10) << std::left << "PRICE"
			<< std::setw(10) << std::right << "QUANTITY"
			<< std::endl;
	for (auto& product : products) {
		
		//std::cout << _storage.dump(product) << std::endl;
		std::cout << std::setw(4) << std::left << product.id 
				<< std::setw(15) << std::left << product.name 
				<< std::setw(10) << std::left << std::fixed << std::setprecision(2) << product.price
				<< std::setw(10) << std::right << product.quantity 
				<< std::endl;
	}
}


