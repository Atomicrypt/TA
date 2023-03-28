/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */


#include "scheduler_priority_rr.h"



SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum) {
    processTotal = 0;
    this->time_quantum = time_quantum;
    avgWait = 0.0;
    avgTurnaround = 0.0;
}

SchedulerPriorityRR::~SchedulerPriorityRR() {

}

void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    initProcList = process_list;
    processTotal = process_list.size();

    for (int i = 0; i < processTotal; i++) {
        processes.push_back(&process_list[i]);
    }
}

void SchedulerPriorityRR::print_results() {
    std::cout << "Average turn-around time = " << avgTurnaround 
              << ", Average waiting = " << avgWait << "\n";
}

void SchedulerPriorityRR::simulate() {
    PCB *curProc;
    double trailing = 0.0;
    double turnCount = 0.0;
    double waitCount = 0.0;

    while (!processes.empty()) {}

    for (int i = 0; i < processTotal; i++) {}

    avgWait = waitCount / processTotal;
    avgTurnaround = turnCount / processTotal;
}
