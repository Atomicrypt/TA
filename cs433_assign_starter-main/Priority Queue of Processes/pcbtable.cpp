/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Alex Nelson, Tyler Felicidario
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   // TODO: add your code here
   // table_size = size;
   table = vector<PCB *>(size);
   // iota(table.begin(), table.end(), nullptr);
   count = 0;
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   // TODO: add your code here
   table.clear();   //clear vector
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    // TODO: add your code here
    return table[idx];
}

/**
 * @brief Add a PCB to the PCBTable.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    // TODO: add your code here
    if(count == 0){
      // table.addNewPCB(pcb->id,pcb->priority,)
    table.insert(table.begin(),pcb);
    }else
    table.insert(table.begin()+idx,pcb);  //insert at index
  
}


// void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
//     // TODO: add your code here
//     if(count == 0){
//       table.addNewPCB(pcb->id,pcb->priority,)
//     }else
//     table.insert(table.begin()+idx,pcb);  //insert at index
  
// }