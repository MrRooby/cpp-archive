#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>


struct Node
{
    std::string roastery, country, region, process;
    int score;
    std::shared_ptr<Node> next = nullptr; 
};

class LinkedList
{
    private:

        std::shared_ptr<Node> head;

        const int nameWidthLong = 27;
        const int nameWidth = 17;
        const char separator = ' ';

    public:
        
        LinkedList();
        LinkedList(const LinkedList &original);
        ~LinkedList();

        LinkedList& operator=(LinkedList original);

        void insert(std::string roastery, std::string country, std::string region, std::string process, int score);
        void init();

        void display(std::string& roastery, std::string& country, std::string& region, std::string& process, int& score);
        void displayFULL();

        void search(std::string value);
        LinkedList bubbleSort(const LinkedList& original);
        void save();
};
