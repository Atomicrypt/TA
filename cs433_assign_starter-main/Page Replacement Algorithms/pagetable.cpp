/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */


#include "pagetable.h"

// Constructor
PageTable::PageTable(int num_pages) {

    //push entrypage objects into "pages" vector
    for (int i = 0; i < num_pages; i++)
    {
        PageEntry p;
        pages.push_back(p);
    }
    
}

// Destructor
PageTable::~PageTable() {
    //releasing page table
    while(!pages.empty())
    {
        pages.pop_back();
    }
}