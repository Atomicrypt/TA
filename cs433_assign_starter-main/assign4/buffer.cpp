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

/**
 * @brief Construct a new Buffer object
 * @param size the size of the buffer
 */
Buffer::Buffer(int size) {
    count = 0;
    maxSize = size;
}

/**
 * @brief Destroy the Buffer object
 */
Buffer::~Buffer() {
    
}

/**
 * @brief Insert an item into the buffer
 * @param item the item to insert
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::insert_item(buffer_item item) {
    if (!is_full()) {
        items.push_back(item);
        count++;
        return true;
    }
    return false;
}


/**
 * @brief Remove an item from the buffer
 * @param item the item to remove
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::remove_item(buffer_item *item) {
    if (!is_empty()) {
        *item = items.front();
        items.pop_front();
        count--;
        return true;
    }
    return false;
}


/**
 * @brief Get the size of the buffer
 * @return the size of the buffer
 */
int Buffer::get_size() {
    return maxSize;
}


/**
 * @brief Get the number of items in the buffer
 * @return the number of items in the buffer
 */
int Buffer::get_count() {
    return count;
}


/**
 * @brief Chceck if the buffer is empty
 * @return true if the buffer is empty, else false
 */
bool Buffer::is_empty() {
    if (count == 0)
        return true;
    else
        return false;
}


/**
 * @brief Check if the buffer is full
 * @return true if the buffer is full, else false
 */
bool Buffer::is_full() {
    if (count >= maxSize)
        return true;
    else
        return false;
}

/**
 * @brief Print the buffer
 */
void Buffer::print_buffer() {
    cout << "Buffer: [";

    for (size_t i = 0; i < items.size(); i++) {
        cout << items[i];
        if (i != items.size() - 1) {
            cout << ", ";
        }
    }

    cout << "]"<<endl;
}
