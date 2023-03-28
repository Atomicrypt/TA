/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here
SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum) {
    processTotal = 0;
    this->time_quantum = time_quantum;
    avgWait = 0.0;
    avgTurnaround = 0.0;
}

SchedulerPriorityRR::~SchedulerPriorityRR() {

}

void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    processTotal = process_list.size();

}

void SchedulerPriorityRR::print_results() {
    std::cout << "Average turn-around time = " << avgTurnaround 
              << ", Average waiting = " << avgWait << "\n";
}

void SchedulerPriorityRR::simulate() {

}
