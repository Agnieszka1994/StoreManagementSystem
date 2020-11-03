#include "ConsoleMenu.h"
#include <sqlite_orm.h>
#include <typeinfo>


int main() {


    ConsoleMenu* menu = new ConsoleMenu();
    menu->run();

    return 0;
}