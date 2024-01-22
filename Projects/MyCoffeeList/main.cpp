#include <iostream>
#include <string>
#include "list.cpp"
#include "menu.cpp"

int main()
{
    LinkedList myCoffeeList;
    Menu menu;
    
    myCoffeeList.init();
    
    menu.mainMenu(myCoffeeList);
}