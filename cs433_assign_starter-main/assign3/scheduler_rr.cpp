/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author ??? Alex Nelson, Tyler Felicidario
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

//constructor for RR Scheduler objects
SchedulerRR(time_quantum)
{

};

/**
    * @brief This function is called once before the simulation starts.
    *        It is used to initialize the scheduler.
    * @param process_list The list of processes in the simulation.
    */
void init(std::vector<PCB>& process_list){
    process_list = {};
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerRR::print_results(){

}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void simulate(){
    
}

SchedulerRR::~SchedulerRR(){

}