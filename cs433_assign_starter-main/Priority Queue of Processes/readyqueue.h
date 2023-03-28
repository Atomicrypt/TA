/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author Alex Nelson, Tyler Felicidario
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code
#pragma once

#include "pcb.h"
using namespace std;

/**
 * @brief A queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 */

// int const maxSize = 105;
class ReadyQueue {
private:
    // TODO: add your private member variables here
    // choose a data structure for the ReadyQueue. No STL class is allowed.
    // int RQ [maxSize] = {};//array of to hold PCB priority nums
    // int *ptr = RQ;//pointer to beginning of array
    PCB *heaparray; // pointer to the array holding the heap
    int capacity;   // the capacity of the heap
    int count;      // how many elements are in the heap


public:
    /**
     * @brief Construct a new ReadyQueue object
     *
     */
    ReadyQueue();

    //utility

    /**
     * @brief Destructor
     */
    ~ReadyQueue() {}

	// You may add additional member functions, but don't change the definitions of the following four member functions.

    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
	void addPCB(PCB* pcbPtr);

    /**
     * @brief Remove and return the PCB with the highest priority from the queue
     *
     * @return PCB*: the pointer to the PCB with the highest priority
     */
	PCB* removePCB();

    /**
     * @brief Returns the number of elements in the queue.
     *
     * @return int: the number of PCBs in the queue
     */
	int size();

     /**
      * @brief Display the PCBs in the queue.
      */
	void displayAll();

  PCB* removeMax();
  void percolateDown(int index);
  void Heap(PCB *values, int length);
  void heapify();
  void heapSort(PCB values[], int length);
  void insert(PCB* value);
  void percolateUp(int index);

    /**
     * @brief swaps the values of the two nodes at index1 and index2
     *
     * @param index1
     * @param index2
     */
    void swap(int index1, int index2);

  //copy constructor
    ReadyQueue(ReadyQueue &q2);

    //operator overloading
    ReadyQueue& operator=(const ReadyQueue& rhs);
};