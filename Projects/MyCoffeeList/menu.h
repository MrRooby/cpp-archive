#pragma once
#include <iostream>
#include "list.h"

class Menu
{
    private:

        int choice = 0;
        int score;

        std::string roastery, country, region, process, variable;
        
        char insertAgain = 'n';
        char byVar = 'y';
        char saveSorted = 'n';
        
        bool exit = false;

    public:
    
        Menu();
        ~Menu();

        void mainMenu(class LinkedList list);
};