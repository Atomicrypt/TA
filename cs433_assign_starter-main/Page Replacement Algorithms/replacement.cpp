/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */

#include <iostream>
#include "replacement.h"


// Constructor
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
	numReplacements = 0;    //number of replacements
    numFaults = 0;          //number of faults
    numRefs = 0;            //number of references

    totalPages = num_pages;     //total number of pages
    totalFrames = num_frames;   //total number of frames

    frameCount = 0;
}

// Destructor
Replacement::~Replacement()
{
    
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    numRefs++;
    
    // If the page is valid, it calls the touch_page function.
    if (page_table[page_num].valid == true) {
        touch_page(page_num);
        
    }
    // If the page is not valid but free frames are available, it calls the load_page function.
    if (page_table[page_num].valid == false && frameCount < totalFrames) {
        load_page(page_num);
        numFaults++;
        frameCount++;
        
        return true;
    }
    // If the page is not valid and there is no free frame, it calls the replace_page function.
    if (page_table[page_num].valid == false && frameCount >= totalFrames) {
        replace_page(page_num);
        numReplacements++;
        numFaults++;
        
        return true;
    }

    return false;
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
        std::cout << "Number of references: \t\t"  << numRefs << std::endl;
		std::cout << "Number of page faults: \t\t" << numFaults << std::endl;
		std::cout << "Number of page replacements: \t"  << numReplacements << std::endl;
}