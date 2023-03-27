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
        processes.push(&process_list[i]);    //push the object into processes (running processes)

        if(process_list[i].burst_time != 0)  //as long as pcb has a burst time
        {
            cout << "Running Process ";
            if(process_list[i].burst_time > mTimeQuant) //if the burst time is > or = the time quantum
            {   
                //case TT is equal to TQ
                cout << process_list[i].name << " for " << mTimeQuant << " time units";
                process_list[i].burst_time -= mTimeQuant;    //adjust the burst time for when the pcb object has to run later
                rQueue.push(process_list[i]);  //push process to readyqueue to be run later
                
            }
            //handle burst times < tq
            else   //otherwise the burst time is less than or equal to the time quantum
            {   
                
                cout << process_list[i].name << " for " << process_list[i].burst_time << " time units";
                process_list[i].burst_time -= process_list[i].burst_time;    //since BT < TQ, BT set to 0 since process is finished
                
            }

            cout << endl; 
        }

        if(!rQueue.empty())  //if the ready queue of processes with greater BT than the TQ is not empty
        {
            process_list.push_back(rQueue.front()); //place the process back into the end of the process list 
            processes.push(&rQueue.front());
            rQueue.pop();   //pop the process from the ready queue since it is now done being evaluated
            processTotal++;
        }
        
    }
}


/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerRR::print_results(){
    cout << "Average turnaround time = " << avgTurnaround 
                << ", Average wait time = " << avgWait << "\n";
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
    double trailing = 0;    // Total elapsed process time
    double trailingSum = 0;
    processTotal = processes.size();

    unordered_map<string, PCB*> umap;  // PCBname, PCBpointer

        // Print array from T1
        cout << "process total: " << processTotal;
    for (int i = 0; i < processTotal; i++) {                    //###### DEBUG NEEDED *processTotal* ######
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