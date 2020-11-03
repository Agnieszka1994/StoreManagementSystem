#include "ConsoleMenu.h"
#include <sqlite_orm.h>
#include <typeinfo>


using namespace sqlite_orm;
int main(int, char**) {


    ConsoleMenu* menu = new ConsoleMenu();
    menu->run();

    return 0;
}