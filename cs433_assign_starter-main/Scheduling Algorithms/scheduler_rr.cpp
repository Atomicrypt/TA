/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Alex Nelson, Tyler Felicidario
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"
#include <string>
#include <unordered_map>
#include <algorithm>


/**
 * @brief Construct a new SchedulerRR object
 */
SchedulerRR::SchedulerRR(int time_quantum){
    mTimeQuant = time_quantum;
    avgTurnaround = 0.0;
    avgWait = 0.0;
    processTotal = 0;
}

/**
 * @brief Destroy the SchedulerRR object
 */
SchedulerRR::~SchedulerRR(){

}


/**
* @brief This function is called once before the simulation starts.
*        It is used to initialize the scheduler.
* @param process_list The list of processes in the simulation.
*/
void SchedulerRR::init(std::vector<PCB>& process_list){

    processTotal = process_list.size();
    initProcList = process_list;    // Initial process list

    for (int i=0 ; i<processTotal; i++)//for each pcb object in proccess_list                   //###### DEBUG NEEDED *processTotal* ######
    {
        readyQueue.push(&process_list[i]);         
    }     
    
}


/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerRR::print_results(){
    cout << "Average turn-around time = " << avgTurnaround 
         << ", Average waiting = " << avgWait << "\n";
}


/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerRR::simulate(){
    /*
    
    1)update elapsed time for the length of each cpu burst time
    2)if process burst time > time quantum, must place process in 
        rqueue and run next process
    3)continue until all processes are gone through then 
    finish the processes from rqueue
    */

    double currentTime = 0;    // overall burst time of each process
    double totalTime = 0;
    processTotal = readyQueue.size();


    unordered_map<string, PCB*> umap;  // PCBname, PCBpointer
    PCB* proc;

    while(!readyQueue.empty())
    {
        proc = readyQueue.front();  //initialize process ptr for each process
        runningQueue.push(proc);
        
        //update remaining time and wait time of process after running
        proc->time_remaining = proc->burst_time;
        cout << "Current Time " << currentTime << endl;
        cout << "Current Time Sum " << totalTime << endl; 
        if(proc->time_remaining > mTimeQuant)   //for process w/ burst time greater than time quantum
        {
            cout << "Running process " << proc->name << " for " 
                  << mTimeQuant << " time units." << endl;

            //updated elapsed time, remaining burst time, and the burst time then push processes back to ready queue
            currentTime += mTimeQuant; 
            proc->time_remaining -= mTimeQuant; 
            proc->burst_time -= mTimeQuant; 
            readyQueue.push(proc);

        } else  //remaining burst time is less than time quantum
        { 
            cout << "Running process " << proc->name << " for " 
                  << proc->burst_time << " time units." << endl;

            //update elapsed time, turnaround, remaining burst time, burst time, and total time
            currentTime += proc->time_remaining; 
            proc->r_turn_time += currentTime;  
            proc->time_remaining = 0;   //since process finishes in this time, its burst time can just be 0 
            proc->burst_time = 0;
            totalTime += currentTime; 

        }
        
        proc->r_wait_time = proc->r_turn_time - proc->burst_time;
        //unconditionally add process to map and pop process from readyqueue 
        umap[proc->name] = proc;        // Access PCB by name, set pointer to PCB
        readyQueue.pop();
    }
        

    avgWait =  (totalTime - currentTime) / processTotal;    // Calculate Average Wait Time
    avgTurnaround = totalTime / processTotal;             // Calculate Average Turnaround Time

    for (int i = 0; i < processTotal; i++) {    // Prints T1 to T8
        PCB* proc = umap[initProcList[i].name]; // Return PCB object
        std::cout << initProcList[i].name << " turnaround time "
                  << proc->r_turn_time
                  << ", waiting time = " << proc->r_wait_time << endl;
    }
}