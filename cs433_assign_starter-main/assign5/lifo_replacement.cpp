/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief A class implementing the LIFO page replacement algorithms
 * @version 0.1
 */

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    
}

LIFOReplacement::~LIFOReplacement() {
    
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    page_table[page_num].frame_num = max_frames - num_frames;
    page_table[page_num].valid = true;
    page_stack.push(page_num);
    num_frames--;
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    // TODO: Add necessary code here
    return 0;
}