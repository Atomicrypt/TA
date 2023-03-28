/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.h
 * @author Alex Nelson, Tyler Felicidario
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */


#ifndef ASSIGN3_SCHEDULER_PRIORITY_RR_H
#define ASSIGN3_SCHEDULER_PRIORITY_RR_H

#include "scheduler.h"
#include <list>
#include <vector>

class SchedulerPriorityRR : public Scheduler {
private:
    list<PCB *> processes;
    list<PCB *> readyQueue;
    std::vector<PCB> initProcList;
    int processTotal;
    int time_quantum;
    double avgWait;
    double avgTurnaround;

public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriorityRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriorityRR() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;

};


#endif //ASSIGN3_SCHEDULER_PRIORITY_RR_H
