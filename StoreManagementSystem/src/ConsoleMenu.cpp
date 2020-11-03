#include "ConsoleMenu.h"
#include "PassGenerator.h"

//using namespace sqlite_orm;
//auto _storage = make_storage("test_db.sqlite",
//	make_table("users",
//		make_column("id", &User::id, autoincrement(), primary_key()),
//		make_column("type_id", &User::typeId),
//		make_column("login", &User::login),
//		make_column("password", &User::password)),
//	make_table("products",
//		make_column("id", &Product::id, autoincrement(), primary_key()),
//		make_column("name", &Product::name),
//		make_column("price", &Product::price),
//		make_column("quantity", &Product::quantity)),
//	make_table("user_types",
//		make_column("id", &UserType::id, autoincrement(), primary_key()),
//		make_column("name", &UserType::name, default_value("user"))));




ConsoleMenu::ConsoleMenu()
{
	_storage.sync_schema();
	running = true;
	userTypeLogged = NULL;
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
	std::cout << "3. Display stock" << std::endl;
	std::cout << "0. Log out" << std::endl;
}

void ConsoleMenu::logIn()
{
}



Product ConsoleMenu::_insertProduct(std::string name, float price, int quantity)
{
	Product new_product = { -1, name, price, quantity};
	new_product.id = _storage.insert(new_product); // insert returns inserted id
	return new_product;
}

User ConsoleMenu::_insertCustomer(std::string name)
{
	User new_user = { -1, 2, name + "_" + random_string(4), random_string(8) };
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