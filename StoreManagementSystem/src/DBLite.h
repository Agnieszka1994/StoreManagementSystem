#pragma once
#include <sqlite_orm.h>
#include <string>
#include <iostream>

using namespace sqlite_orm;

struct User {
    int id;
    int typeId;
    std::string firstName;
    std::string password;
};

struct UserType {
    int id;
    std::string name;
};

struct Product {
    std::string name;
    float price;
    int quantity;
    int id;
};

 





////  insert returns inserted id
//paul.id = storage.insert(paul);

//storage.insert(Employee{
//    -1,
//    "Allen",
//    25,
//    "Texas",
//    15000.00,
//    });