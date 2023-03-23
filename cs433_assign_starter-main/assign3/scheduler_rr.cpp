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

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

//constructor for RR Scheduler objects
SchedulerRR::SchedulerRR(int time_quantum){
    mTimeQuant = time_quantum;
    avgTurnaround = 0.0;
    avgWait = 0.0;
    processTotal = 0;
}

/**
    * @brief This function is called once before the simulation starts.
    *        It is used to initialize the scheduler.
    * @param process_list The list of processes in the simulation.
    */
void SchedulerRR::init(std::vector<PCB>& process_list){
    
    processTotal = process_list.size();
    initProcList = process_list;    // Initial process list

    // sort(process_list.begin(), process_list.end(), [](PCB &left, PCB &right) {
    //     return left.burst_time < right.burst_time;
    // });
cout << "TEST " << processTotal << " TEST" << endl;
    for (int i = 0; i < processTotal; i++)                   //###### DEBUG NEEDED *processTotal* ######
    {
    processes.push(&process_list[i]);
    
    
    // cout << "Running process " << process_list[i].name << " for " 
    //             << process_list[i].burst_time << " time units." << endl;
        if(process_list[i].burst_time != 0)
        {
            cout << "Running Process ";
            if(process_list[i].burst_time >= mTimeQuant)
            {   
                //case TT is equal to TQ
                process_list[i].r_turn_time += mTimeQuant;    
                cout << process_list[i].name << " for " << mTimeQuant << " time units";
                process_list[i].burst_time -= mTimeQuant;
                rQueue.push(process_list[i]);  //push process to readyqueue to be run later
                
            }
            //handle burst times < tq
            else if(process_list[i].burst_time < mTimeQuant && process_list[i].burst_time != 0)
            {   
                
                cout << process_list[i].name << " for " << process_list[i].burst_time << " time units";
                process_list[i].r_turn_time += process_list[i].burst_time;   
                
                process_list[i].burst_time = 0;    //since BT < TQ, BT set to 0 since process is finished
                
            }
            cout << endl;
        if(rQueue.size() != 0)
        {
        process_list.push_back(rQueue.front());
        rQueue.pop();
        
        }
        }
    }
}
    
    // vector<PCB> scheduler; 
//     for(int i = 0; i < process_list.size(); i++){
//         scheduler.push_back(process_list[i]);   //place processes in scheduler
//     }

//     for(int i =  0; i < scheduler.size(); i++)
//    {
//     PCB proc = scheduler[i];
//     if(scheduler[i].burst_time != 0)
//     {
//         cout << "Running Process ";
//         if(scheduler[i].burst_time >= mTimeQuant)
//         {
//             proc.r_turn_time += mTimeQuant;    //TT is equal to TQ
//             cout << scheduler[i].name << " for " << mTimeQuant << " time units";
//             scheduler[i].burst_time -= mTimeQuant;
//             rQueue.push(scheduler[i]);  //push process to readyqueue to be run later
            
//         }
//         //handle burst times < tq
//         else if(scheduler[i].burst_time < mTimeQuant && scheduler[i].burst_time != 0)
//         {
//             cout << scheduler[i].name << " for " << scheduler[i].burst_time << " time units";
//             proc.r_turn_time += scheduler[i].burst_time;   //TT is equal to BT
//             scheduler[i].burst_time = 0;    //since BT < TQ, BT set to 0 since process is finished
//         }
//         cout << endl;

//         if(rQueue.size() != 0)

//         {
//         scheduler.push_back(rQueue.front());
//         rQueue.pop();
//         }
//     }
//    }


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

    unordered_map<string, PCB*> umap;  // PCBname, PCBpointer

        // Print array from T1
    for (int i = 0; i < processTotal; i++) {                    //###### DEBUG NEEDED *processTotal* ######
        cout << "TEST "<< processTotal << " TESTING" << endl;
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

SchedulerRR::~SchedulerRR(){

}