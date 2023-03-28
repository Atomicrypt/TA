#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
     //TODO: add your code here
   int maxSize = 101;
   capacity = maxSize;
   heaparray = new PCB [capacity];
  count = 0; //nothing in queue yet
 }

/**
 * @brief Copy Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue(ReadyQueue &q2)  {
     //TODO: add your code here
   capacity = q2.capacity;
   count = q2.count;
   heaparray = new PCB [capacity];
 }


//operator= overloading funct
ReadyQueue& ReadyQueue::operator=(const ReadyQueue& rhs){
  if(&rhs != this){
    this->capacity = rhs.capacity;//capacity now equal to given size
    this->count = rhs.count;//array size needs to be empty, so initialize array size
    delete[] heaparray;
    heaparray = new PCB[rhs.capacity];//creating array to hold all pcb data, creating new space for pcb bsed on capacity size
  }
  return *this;
}


/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {//will look like a max heap
    //TODO: add your code here
    // When adding a PCB to the queue, you must change its state to READY.
    pcbPtr->setState(ProcState::READY); //set state of current PCB to ready
    // cout << "Adding: "<< pcbPtr->id << endl;//remove after testing
  this->insert(pcbPtr);
}

/**
 * @brief  inserts a value into the heap
 *
 */
void ReadyQueue::insert(PCB* value) {
    if (count == capacity) {
        // Resize Heap array
        PCB* new_heaparray = new PCB[capacity * 2];
        for (int i = 0; i < count; i++) {
            new_heaparray[i] = heaparray[i];
        }
        capacity *= 2;
        delete[] heaparray;
        heaparray = new_heaparray;
    }
    else {
        // Add the new value to the end of the array
        heaparray[count] = *value;
        count++;

        // Percolate up from the last index to restore the heap property
        percolateUp(count - 1);
    }
    
}

/**
 * @brief  Swaps the values in the heap at index1 and index2
 */
void ReadyQueue::swap(int index1, int index2) {
    PCB temp = heaparray[index1];
    heaparray[index1] = heaparray[index2];
    heaparray[index2] = temp;
}


/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    //TODO: add your code here
    // When removing a PCB from the queue, you must change its state to RUNNING.

  if(count>0){
    return removeMax();  //get returned value
  }else{
    return 0;
  }
}

/**
 * @brief  Removes the max value from the heap
 * @return the value that was removed
 */
PCB* ReadyQueue::removeMax() {
    // If heap is empty
    if (count == 0) {
        return 0;
    }
    else {
        // Save the max value from the root of the heap
        PCB* maxValue = &heaparray[0];

        // Move the last item in the array into index 0
        PCB replaceValue = heaparray[count - 1];
        count--;
        if (count > 0) {
            heaparray[0] = replaceValue;

            // Percolate down to restore max-heap property
            percolateDown(0);
        }

        // Return the max value
        return maxValue;
    }
}

/**
 * @brief  Runs percolate down on the heap for the node stored in index.
 */
void ReadyQueue::percolateDown(int index) {
    int childIndex = 2 * index + 1;
    int value = heaparray[index].priority;

    while (childIndex < count) {
        // Find the max among the node and all the node's children
        int maxValue = value;
        int maxIndex = -1;
        int i = 0;
        while (i < 2 && i + childIndex < count) {
            if (heaparray[i + childIndex].priority > maxValue) {
                maxValue = heaparray[i + childIndex].priority;
                maxIndex = i + childIndex;
            }
            i++;
        }

        // Check for a violation of the max-heap property
        if (maxValue == value) {
            return;
        }
        else {
            // Swap heaparray[index] and heaparray[maxIndex]
            swap(index, maxIndex);

            // Continue loop from the max index node
            index = maxIndex;
            childIndex = 2 * index + 1;
        }
    }
}


/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    //TODO: add your code here
  return count;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    //TODO: add your code here
    cout << "PCBs in readyqueue: ";
  // PCB * ptr;
  // while(RQ)
    // insertion_sort(RQ,4);
    for(int i=0; i<count;i++){
        cout << heaparray[i].getID() << ' ';
          // << RQ[i].getId() << " ,PRIORITY: " << RQ[i].getPriority() << " ,STATE: " << RQ[i].getState() ;
    } cout << endl;
}

/**
 * @brief  Runs percolate up on the heap for the node stored in index.
 */
void ReadyQueue::percolateUp(int index) {
    while (index > 0) {
        // Compute the parent node's index
            int parent = (index - 1) / 2;

        // Check for a violation of the max-heap property
        if (heaparray[index].getPriority() <= heaparray[parent].getPriority()) {
            // No violation, so percolate up is done
            return;
        }
        else {
            // Swap heaparray[index] and heaparray[parent]
            swap(index, parent);

            // Continue the loop from the parent node
            index = parent;
        }
    }
}