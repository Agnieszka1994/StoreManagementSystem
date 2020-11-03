#include "ConsoleMenu.h"
#include <sqlite_orm.h>
#include <typeinfo>
//struct UserB {
//	int id = 0;
//	int typeId;
//	std::string login = "";
//	std::string password;
//};
//
//struct UserTypeB {
//	int id;
//	std::string name;
//};
//
//struct ProductB {
//	int id;
//	std::string name;
//	double price;
//	int quantity;
//};
//
//struct OrderB {
//	int id;
//	int userId;
//	int productId;
//	int quantity;
//	std::string status;
//};

using namespace sqlite_orm;

//auto store = make_storage("test_db.sqlite",
//		make_table("users",
//			make_column("id", &User::id, autoincrement(), primary_key()),
//			make_column("type_id", &User::typeId),
//			make_column("login", &User::login),
//			make_column("password", &User::password)),
//		make_table("products",
//			make_column("id", &Product::id, autoincrement(), primary_key()),
//			make_column("name", &Product::name),
//			make_column("price", &Product::price),
//			make_column("quantity", &Product::quantity)),
//		make_table("orders",
//			make_column("id", &Order::id, autoincrement(), primary_key()),
//			make_column("userId", &Order::userId),
//			make_column("productId", &Order::productId),
//			make_column("quantity", &Order::quantity),
//			make_column("status", &OrderB::status)),
//		make_table("user_types",
//			make_column("id", &UserType::id, autoincrement(), primary_key()),
//			make_column("name", &UserType::name, default_value("user"))));

int main() {

	//std::cout << typeid(store).name() << std::endl;

    ConsoleMenu* menu = new ConsoleMenu();
    menu->run();

    return 0;
}