#include "ConsoleMenu.h"
#include "PassGenerator.h"

ConsoleMenu::ConsoleMenu()
{
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
				break;
			case 0:
				exit(0);
			}
		}
		while (userTypeLogged == 1) {
			this->showAdmin();
			
		}
		while (userTypeLogged == 2) {
			this->showUser();
			
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
}

void ConsoleMenu::logIn()
{
}

void ConsoleMenu::createCustomerAccount()
{
}

void ConsoleMenu::insertProduct(std::string name, float price, int quantity)
{
	Product new_product = { name, price, quantity, -1 };
	//  insert returns inserted id
	//new_product.id = storage.insert(new_product);
}

void ConsoleMenu::insertCustomer(std::string firstName)
{
	User new_user = { -1, 2, firstName, random_string(8) };
	//  insert returns inserted id
	//new_user.id = storage.insert(new_user);
	std::cout << "Your login: " << new_user.firstName << std::endl;
	std::cout << "Password: " << new_user.password << std::endl;
}
