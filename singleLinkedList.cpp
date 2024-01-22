#include "singleLinkedList.h"


LinkedList::LinkedList(): head(nullptr) {}


LinkedList::LinkedList(const LinkedList &original)
{
    head = nullptr;
    std::shared_ptr<Node> current = original.head;
    while(current != nullptr)
    {
        insert(current->data);
        current = current->next;
    }
}
 

LinkedList::~LinkedList(){}


LinkedList &LinkedList::operator=(LinkedList original)
{
    std::swap(head, original.head);
    return *this;
}


void LinkedList::insert(int data)
{
    std::shared_ptr<Node> newNode = std::make_shared<Node>();

    newNode->data = data;
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
    std::ifstream readfile( "savefile.txt" );

    std::string line;

    while (std::getline(readfile, line)) 
    {
        std::istringstream iss(line);

        int data;

        if (iss >> data) 
        {
            insert(data);
        } 
    }
}


void LinkedList::search(int& value)
{
    if(head == nullptr)
    {
        std::cout << "The list is empty!" << std::endl;
    }
    else
    {
        std::shared_ptr<Node> current = head;

        std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Data]";

        while(current != nullptr)
        {
            if(current->data == value)
            {
                display(current->data);
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
    int tempData;

    for (prev = sortedList.head; prev; prev = prev->next)
    {
        for(curr = prev->next; curr; curr = curr->next)
        {
            if(prev->data < curr->data)
            {
                tempData = prev->data;
                prev->data = curr->data;
                curr->data = tempData;                
            }
        }
    }
    return sortedList;
}


void LinkedList::display(int& data)
{
    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << data;
    std::cout << std::endl;
}


void LinkedList::displayFULL()
{
    std::shared_ptr<Node> current = head;

    std::cout << std::left << std::setw(nameWidth) << std::setfill(separator) << "[Data]" << std::endl;

    while(current != nullptr)
    {
        display(current->data);
        current = current->next;
    }
}


void LinkedList::save()
{
    std::ofstream writeFile;
	writeFile.open( "savefile.txt");

	std::shared_ptr<Node> current = head;

	while( current != nullptr )
	{
		writeFile << current->data << std::endl;
		current = current->next;
	}
	
	writeFile.close();
}