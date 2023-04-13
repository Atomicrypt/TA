/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief Implementation file for the buffer class
 * @version 0.1
 */


//TREAT BUFFER AS A QUEUE

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"

// TODO: Add your implementation of the buffer class here
Buffer::Buffer(int size) {
    size = 5;
    count = 0;
}

Buffer::~Buffer() {
    
}

bool Buffer::insert_item(buffer_item item) {
    if (!is_full()) {
        items.push(item);
        count++;
        return true;
    }
}

bool Buffer::remove_item(buffer_item *item) {
    if (!is_empty()) {
        *item = items.front();
        items.pop();
        count--;
        return true;
    }
}

int Buffer::get_size() {
    return size;
}

int Buffer::get_count() {
    return count;
}

bool Buffer::is_empty() {
    if (count == 0)
        return true;
    else
        return false;
}

bool Buffer::is_full() {
    if (count >= maxSize)
        return true;
    else
        return false;
}

void Buffer::print_buffer() {
    //for (std::list<buffer_item>::iterator it = items.begin(); it != items.end(); ++it) {
    //    std::cout *it;
    //} 
}
