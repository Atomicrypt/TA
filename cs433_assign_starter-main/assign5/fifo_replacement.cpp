/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    
}
FIFOReplacement::~FIFOReplacement() {
    
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    page_table[page_num].frame_num = frameCount;   // Assigning it
    page_table[page_num].valid = true;
    page_queue.push(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    int front_num = page_queue.front(); // Assign page number to front of queue
    page_queue.pop();
    page_queue.push(page_num);
    page_table[page_num].valid = true;
    page_table[front_num].valid = false;
    
    return 0;
}