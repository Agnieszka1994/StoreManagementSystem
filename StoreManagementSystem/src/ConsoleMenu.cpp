#include "ConsoleMenu.h"
#include "PassGenerator.h"
#include "InputHandler.h"

void idNotFoundMsg(int id) {
	std::cout << "ID " << id << " not found!" << std::endl;
	std::cout << "Please try again." << std::endl;
}

void noOptionMsg() {
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
				noOptionMsg();
				system("pause");
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
				cancelOrder();
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
			case 8:
				displayUsersStatistic();
				system("pause");
				break;		
			case 0:
				logOut();
				system("pause");
				break;
			default:
				noOptionMsg();
				system("pause");
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
				checkOrderById();
				system("pause");
				break;
			case 3:
				displayAllOrdersUser();
				system("pause");
				break;
			case 4:
				deleteUserAccount();
				system("pause");
				break;
			case 0:
				logOut();
				system("pause");
				break;
			default:
				noOptionMsg();
				system("pause");
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
	std::cout << "4. Delete account" << std::endl;
	std::cout << "0. Log out" << std::endl;
}

void ConsoleMenu::showAdmin()
{
	std::cout << "1. Add products" << std::endl;
	std::cout << "2. Cancel order" << std::endl;
	std::cout << "3. Display all orders" << std::endl;
	std::cout << "4. Complete order" << std::endl; 
	std::cout << "5. Display stock" << std::endl;
	std::cout << "6. Delete product from stock" << std::endl;
	std::cout << "7. Add or subtract qty from stock" << std::endl;
	std::cout << "8. Display Users Statistics" << std::endl;
	std::cout << "0. Log out" << std::endl;
}

void ConsoleMenu::_displayUserHeader()
{
	std::cout << std::setw(9) << std::left << "Order ID"
		<< std::setw(15) << std::left << "PROD. NAME"
		<< std::setw(11) << std::left << "PROD. ID"
		<< std::setw(11) << std::left << "ORDER QTY"
		<< std::setw(11) << std::left << "UNIT PRICE"
		<< std::setw(11) << std::left << "TOTAL PRICE"
		<< std::setw(11) << std::right << "STATUS"
		<< std::endl;
}

void ConsoleMenu::_displayAdminHeader() 
{
	std::cout << std::setw(9) << std::left << "Order ID"
		<< std::setw(8) << std::left << "USER ID"
		<< std::setw(15) << std::left << "USER NAME"
		<< std::setw(15) << std::left << "PROD. NAME"
		<< std::setw(11) << std::left << "PROD. ID"
		<< std::setw(11) << std::left << "ORDER QTY"
		<< std::setw(11) << std::left << "UNIT PRICE"
		<< std::setw(11) << std::left << "TOTAL PRICE"
		<< std::setw(11) << std::right << "STATUS"
		<< std::endl;
}

void ConsoleMenu::_displayStockHeader() 
{
	std::cout << std::setw(4) << std::left << "ID"
		<< std::setw(15) << std::left << "NAME"
		<< std::setw(10) << std::left << "PRICE"
		<< std::setw(10) << std::right << "QUANTITY"
		<< std::endl;
}

void ConsoleMenu::_displayUserStatsHeader()
{
	std::cout << std::setw(4) << std::left << "ID"
		<< std::setw(15) << std::left << "NAME"
		<< std::setw(12) << std::left << "TOTAL ORDERS"
		<< std::setw(12) << std::left << "TOTAL QTY"
		<< std::setw(13) << std::right << "TOTAL PRICE"
		<< std::endl;
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
		idNotFoundMsg(id);
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
		if (choice == 'Y' or choice == 'y') {
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
		idNotFoundMsg(id);
		return;
	}
}

void ConsoleMenu::cancelOrder()
{
	displayActiveOrdersAdmin();
	std::cout << "Please enter order ID:" << std::endl;
	int id = getChoice<int>();
	if (auto order = _storage.get_pointer<Order>(id)) {
		std::cout << "Order from user: " << order->userId << std::endl;
		std::cout << "Are you sure to cancel Order nr: " << order->id << "?  Y/N" << std::endl;
		char choice = getChoice<char>();
		if (choice == 'Y' or choice == 'y') {
			order->status = "canceled";
			_storage.update(*order);
			std::cout << "Order: " << id << " " << order->id << " has been canceled." << std::endl;
			return;
		}
		else {
			std::cout << "Order not canceled." << id << std::endl;
			return;
		}
	}
	else {
		idNotFoundMsg(id);
		return;
	}
}

void ConsoleMenu::deleteUserAccount()
{
	auto ordersByUserId = _storage.get_all<Order>(
		where(c(&Order::userId) == userIDLogged and c(&Order::status) == "new"));
	if (ordersByUserId.size() == 0) {
		std::cout << "Are you sure to delete Your account? Y/N" << std::endl;
		char choice = getChoice<char>();
		if (choice == 'Y' or choice == 'y') {
			_storage.remove<User>(userIDLogged);
			logOut();
			std::cout << "Your account has been deleted." << std::endl;
			return;
		}
		else {
			return;
		}
	}
	else {
		std::cout << "You have active orders! Impossible to delete account?" << std::endl;
		return;
	}
}

void ConsoleMenu::displayAllOrdersAdmin()
{
	auto ordersByUserId = _storage.get_all<Order>(order_by(&Order::id));
	if (ordersByUserId.size() == 0) {
		std::cout << "No orders found" << std::endl;
	}
	else {
		auto ordersDetails = _storage.select(columns(&Order::id, &User::id, &User::login, 
			&Product::name, &Product::id, &Order::quantity, &Product::price, &Order::status),
			inner_join<Product>(on(c(&Product::id) == &Order::productId)),
			inner_join<User>(on(c(&User::id) == &Order::userId)));
		_displayAdminHeader();
		displayOrdersAdmin(ordersDetails);
	}
}

void ConsoleMenu::displayActiveOrdersAdmin()
{
	auto ordersByUserId = _storage.get_all<Order>(order_by(&Order::id));
	if (ordersByUserId.size() == 0) {
		std::cout << "No orders found" << std::endl;
	}
	else {
		auto ordersDetails = _storage.select(columns(&Order::id, &User::id, &User::login,
			&Product::name, &Product::id, &Order::quantity, &Product::price, &Order::status),
			inner_join<Product>(on(c(&Product::id) == &Order::productId)),
			inner_join<User>(on(c(&User::id) == &Order::userId)),
			where(c(&Order::status) == "new"));
		_displayAdminHeader();
		displayOrdersAdmin(ordersDetails);
	}
}

void ConsoleMenu::completeOrder()
{
	displayActiveOrdersAdmin();
	std::cout << "Please enter order ID:" << std::endl;
	int id = getChoice<int>();
	if (auto order = _storage.get_pointer<Order>(id)) {
		if (auto product = _storage.get_pointer<Product>(order->productId)) {
			if (product->quantity >= order->quantity) {
				product->quantity -= order->quantity;
				order->status = "completed";
				std::cout << "Order ID: " << order->id << " is ready" << std::endl;
				std::cout << "Order quantity:         " << order->quantity << std::endl;
				std::cout << "Qty remaining in stock: " << product->quantity << std::endl;
				std::cout << "Please confirm completion. Y/N" << std::endl;
				char choice = getChoice<char>();
				if (choice == 'Y' or choice == 'y') {
					_storage.update(*product);
					_storage.update(*order);
					std::cout << "Order completed successfully!" << std::endl;
					return;
				}
				else {
					std::cout << "Order NOT completed" << id << std::endl;
					return;
				}

			}
			else {
				std::cout << "Quantity insufficient: " << product->id << " "
					<< product->name << std::endl;
			}
		}
		else {
			std::cout << "No product available in stock: " << product->id << " " 
				<< product->name << std::endl;
		}
	}
	else {
		idNotFoundMsg(id);
		return;
	}
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
		idNotFoundMsg(id);
		return;
	}
}

void ConsoleMenu::displayStock()
{
	auto products = _storage.get_all<Product>(order_by(&Product::id));
	std::cout << std::endl << products.size() << " products available in stock:" << std::endl << std::endl;
	_displayStockHeader();
	displayProducts(products);
}

void ConsoleMenu::displayUsersStatistic()
{
	auto users = _storage.select(columns(&User::id, &User::login),
			inner_join<Order>(on(c(&Order::userId) == &User::id)), 
			where(c(&Order::status) == "new"),
			group_by(&User::login));
	for (auto& user : users) {
		auto countOrders = _storage.count(&Order::id, where(c(&Order::userId) == get<0>(user) and c(&Order::status) == "new"));
		std::cout << get<1>(user) << " - total active orders: " << countOrders << std::endl;		
	}
	if (users.size() == 0) {
		std::cout << "No users with open orders!" << std::endl;
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
		idNotFoundMsg(id);
		return;
	}
}

void ConsoleMenu::checkOrderById()
{
	std::cout << "Please enter order ID:" << std::endl;
	int id = getChoice<int>();
	if (auto order = _storage.get_pointer<Order>(id)) {
		std::cout << "Order: " << order->userId << std::endl;
		std::cout << "Status: " << order->status << std::endl;
		return;
	}
	else {
		idNotFoundMsg(id);
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
		auto ordersDetails = _storage.select(columns(&Order::id, &Product::name, 
			&Product::id, &Order::quantity, &Product::price, &Order::status),
			inner_join<Product>(on(c(&Product::id) == &Order::productId)),
			where(c(&Order::userId) == userIDLogged));
		_displayUserHeader();
		displayOrdersUser(ordersDetails);
	}
}

