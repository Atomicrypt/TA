/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Alex Nelson, Tyler Felicidario
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_fcfs.h"
#include "scheduler_sjf.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

/**
 * @brief Construct a new SchedulerFCFS object
 */
SchedulerFCFS::SchedulerFCFS() {  // Constructor
    avgWait = 0.0;
    avgTurnaround = 0.0;
    processTotal = 0;
}

/**
 * @brief Destroy the SchedulerFCFS object
 */
SchedulerFCFS::~SchedulerFCFS() { // Destructor

}

/**
* @brief This function is called once before the simulation starts.
*        It is used to initialize the scheduler.
* @param process_list The list of processes in the simulation.
*/
void SchedulerFCFS::init(std::vector<PCB>& process_list) {
    processTotal = process_list.size();
    initProcList = process_list;    // Initial process list

    for (int i = 0; i < processTotal; i++) {
        processes.push(&process_list[i]);
        
        std::cout << "Running process " << process_list[i].name << " for " 
                  << process_list[i].burst_time << " time units." << endl;
    }
}


/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerFCFS::simulate() {
    double trailing = 0;    // Total elapsed process time
    double trailingSum = 0;

    std::unordered_map<string, PCB*> umap;  // PCBname, PCBpointer

    // Print array from T1
    for (int i = 0; i < processTotal; i++) {
        PCB* proc = processes.front();  // First element of the queue
        proc->r_wait_time = trailing;   // Set relative wait time
        trailing += proc->burst_time;   // Add burst time to trailing
        proc->r_turn_time = trailing;   // Set relative turnaround time
        umap[proc->name] = proc;        // Access PCB by name, set pointer to PCB
        trailingSum += trailing;        // Cumulative sum of trailing
        processes.pop();                // Move to next process
    }

    avgWait = ((trailingSum - trailing) / processTotal);    // Calculate Average Wait Time
    avgTurnaround = trailingSum / processTotal;             // Calculate Average Turnaround Time

    for (int i = 0; i < processTotal; i++) {    // Prints T1 to T8
        PCB* proc = umap[initProcList[i].name]; // Return PCB object
        std::cout << initProcList[i].name << " turnaround time "
                  << proc->r_turn_time
                  << ", waiting time = " << proc->r_wait_time << endl;
    }
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerFCFS::print_results() {
    std::cout << "Average turn-around time = " << avgTurnaround 
              << ", Average waiting = " << avgWait << "\n";
}