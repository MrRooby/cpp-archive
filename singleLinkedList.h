#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

//test

struct Node
{
    int data;
    std::shared_ptr<Node> next = nullptr; 
};

class LinkedList
{
    private:

        std::shared_ptr<Node> head;

        const int nameWidth = 17;
        const char separator = ' ';

    public:
        
        LinkedList();
        LinkedList(const LinkedList &original);
        ~LinkedList();

        LinkedList& operator=(LinkedList original);

        void insert(int data);
        void init();

        void display(int& data);
        void displayFULL();

        void search(int& value);
        LinkedList bubbleSort(const LinkedList& original);
        void save();
};
