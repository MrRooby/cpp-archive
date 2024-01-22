#include "list.h"


LinkedList::LinkedList(): head(nullptr) {}


LinkedList::LinkedList(const LinkedList &original)
{
    head = nullptr;
    std::shared_ptr<Node> current = original.head;
    while(current != nullptr)
    {
        insert(current->roastery, current->country, current->region, current->process, current->score);
        current = current->next;
    }
}


LinkedList::~LinkedList(){}


LinkedList &LinkedList::operator=(LinkedList original)
{
    std::swap(head, original.head);
    return *this;
}


void LinkedList::insert(std::string roastery, std::string country, std::string region, std::string process, int score)
{
    std::shared_ptr<Node> newNode = std::make_shared<Node>();

    newNode->roastery = roastery;
    newNode->country = country;    
    newNode->region = region;
    newNode->process = process;
    newNode->score = score;
    newNode->next = nullptr;

    if(head == nullptr)
    {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    newNode->next = head;
    head = newNode;
}


void LinkedList::init()
{
    std::ifstream readfile( "listofcoffee.txt" );

    std::string line;

    while (std::getline(readfile, line)) 
    {
        std::istringstream iss(line);

        std::string roastery, country, region, process;
        int score;

        if (iss >> roastery >> country >> region >> process >> score) 
        {
            insert(roastery, country, region, process, score);
        } 
    }
}


void LinkedList::search(std::string value)
{
    if(head == nullptr)
    {
        std::cout << "The list is empty!" << std::endl;
    }
    else
    {
        std::shared_ptr<Node> current = head;

        std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Roastery]";
        std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Country]";
        std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Region]";
        std::cout << std::left << std::setw(nameWidthLong) << std::setfill(separator) << "[Process]";
        std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Score]" << std::endl;

        while(current != nullptr)
        {
            if(current->roastery == value || current->country == value || current->region == value || current->process == value)
            {
                display(current->roastery, current->country, current->region, current->process, current->score);
            }
            current = current->next;
        }
    }
}


LinkedList LinkedList::bubbleSort(const LinkedList& original)
{
    LinkedList sortedList(original);
    std::shared_ptr<Node> prev;
    std::shared_ptr<Node> curr;
    std::string tempCountry;
    std::string tempRoastery;    
    std::string tempRegion;
    std::string tempProcess;
    int tempScore;

    for (prev = sortedList.head; prev; prev = prev->next)
    {
        for(curr = prev->next; curr; curr = curr->next)
        {
            if(prev->score < curr->score)
            {
                tempCountry = prev->country;
                prev->country = curr->country;
                curr->country = tempCountry;

                tempRegion = prev->region;
                prev->region = curr->region;
                curr->region = tempRegion;

                tempRoastery = prev->roastery;
                prev->roastery = curr->roastery;
                curr->roastery = tempRoastery;

                tempProcess = prev->process;
                prev->process = curr->process;
                curr->process = tempProcess;

                tempScore = prev->score;
                prev->score = curr->score;
                curr->score = tempScore;                
            }
        }
    }
    return sortedList;
}


void LinkedList::display(std::string& roastery, std::string& country, std::string& region, std::string& process, int& score)
{
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << roastery;
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << country;
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << region;
    std::cout << std::left << std::setw(nameWidthLong) << std::setfill(separator) << process;
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << score;
    std::cout << std::endl;
}


void LinkedList::displayFULL()
{
    std::shared_ptr<Node> current = head;

    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Roastery]";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Country]";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Region]";
    std::cout << std::left << std::setw(nameWidthLong) << std::setfill(separator) << "[Process]";
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Score]" << std::endl;

    while(current != nullptr)
    {
        display(current->roastery, current->country, current->region, current->process, current->score);
        current = current->next;
    }
}


void LinkedList::save()
{
    std::ofstream writeFile;
	writeFile.open( "listofcoffee.txt");

	std::shared_ptr<Node> current = head;

	while( current != nullptr )
	{
		writeFile << current->roastery << " " << current->country << " " << current->region << " " << current->process << " " << current->score << std::endl;
		current = current->next;
	}
	
	writeFile.close();
}