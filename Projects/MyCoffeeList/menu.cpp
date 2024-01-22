#include "menu.h"

Menu::Menu(){}


Menu::~Menu(){}


void Menu::mainMenu(class LinkedList list)
{
    LinkedList sortedList = list.bubbleSort(list);

    do
    {
        std::cout << "\n\nWelcome to your Coffee List! \nChoose an option (for choice press number in brackets):";
        std::cout << "\n[1] Add a new coffee\n[2] Display my Coffee List\n[3] Search by variable\n[4] Display sorted by score\n[0] Exit";
        std::cout << "\nSelection: ";
        std::cin >> choice;

        switch(choice)
        {
            case 1:

                do
                {
                    std::cout << "\nInsert new coffee in shown pattern (separate data by [space] use [_] if name has multiple words): " << std::endl;
                    std::cout << "[Roastery] [Country of origin] [Region] [Processing] [Personal Score]" << std::endl;
                    std::cin >> roastery >> country >> region >> process >> score;
                    list.insert(roastery, country, region, process, score);

                    std::cout << "\nCoffee added!\nWould you like to add another coffee? [y/n]: "  ;
                    std::cin >> insertAgain;
                } 
                while (insertAgain == 'y' || insertAgain == 'Y');
                list.save();
                std::cout << "\nList saved!";
                break;
            
            case 2:

                std::cout << "\nYour Coffee List: " <<std::endl;
                list.displayFULL();
                break;

            case 3:

                do
                {
                    std::cout << "\nWhich category would you like to display (type in country, roastery, etc.)?:  ";
                    std::cin >> variable;
                    std::cout << std::endl;
                    list.search(variable);
                    std::cout << "\nSearch again? [y/n]:  ";
                    std::cin >> byVar;
                } while (byVar == 'y' || byVar == 'Y');
                break;
            
            case 4:

                std::cout << "\nSorted Coffee List:" <<std::endl;
                sortedList.displayFULL();
                std::cout << "Would you like to save the sorted list? [y/n]:  ";
                std::cin >> saveSorted;
                if(saveSorted == 'y' || saveSorted == 'Y')
                {
                    list = sortedList;
                    list.save();
                    std::cout << "Sorted list saved!" << std::endl;
                }
                break;

            case 0:

                exit = true;
                break;
                
            default:
                break;
    }
    } while (!exit);
}