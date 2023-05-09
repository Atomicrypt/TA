/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */

#include "lru_replacement.h"
#include <algorithm>

LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    
}

LRUReplacement::~LRUReplacement()
{
    
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    // Update your data structure LRU replacement
    auto it = std::find(page_queue.begin(), page_queue.end(), page_num);
    page_queue.erase(it);
    page_queue.push_front(page_num);
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    // Update your data structure LRU replacement and pagetable
    page_table[page_num].frame_num = frameCount; // Assigning it
    page_table[page_num].valid = true; 
    page_queue.push_front(page_num);
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    // Update your data structure LRU replacement and pagetable
    int lru_num = page_queue.back(); // Most used
    page_queue.pop_back();
    page_queue.push_front(page_num); 
    page_table[page_num].valid = true;
    page_table[lru_num].valid = false;
    
    return 0;
}