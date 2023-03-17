/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.h
 * @author Alex Nelson, Tyler Felicidario
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */


#ifndef ASSIGN3_SCHEDULER_SJF_H
#define ASSIGN3_SCHEDULER_SJF_H

#include "scheduler.h"
#include <vector>
#include <queue>

class SchedulerSJF : public Scheduler {
private:
    queue<PCB*> processes;
    double avgWait;
    double avgTurnaround;
    int processTotal;
    std::vector<PCB> initProcList;

public:
    /**
     * @brief Construct a new SchedulerSJF object
     */
    SchedulerSJF();
    /**
     * @brief Destroy the SchedulerSJF object
     */
    ~SchedulerSJF() override;
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
#endif //ASSIGN3_SCHEDULER_SJF_H
