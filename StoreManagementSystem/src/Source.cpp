#include "ConsoleMenu.h"
#include "DBLite.h"


struct UserA {
    int id;
    std::string firstName;
    std::string lastName;
    int birthDate;
    std::shared_ptr<std::string> imageUrl;
    int typeId;
};

struct UserTypeA {
    int id;
    std::string name;
    std::string comment;
};

int main(int, char**) {
   

    using namespace sqlite_orm;
    auto storage = make_storage("db.sqlite",
        make_table("users",
            make_column("id", &UserA::id, autoincrement(), primary_key()),
            make_column("first_name", &UserA::firstName),
            make_column("last_name", &UserA::lastName),
            make_column("birth_date", &UserA::birthDate),
            make_column("image_url", &UserA::imageUrl),
            make_column("type_id", &UserA::typeId)),
        make_table("user_types",
            make_column("id", &UserTypeA::id, autoincrement(), primary_key()),
            make_column("name", &UserTypeA::name),
            make_column("comment", &UserTypeA::comment, default_value("user"))));
    ConsoleMenu menu = ConsoleMenu();
    menu.run();

    return 0;
}