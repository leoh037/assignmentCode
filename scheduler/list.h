/**
 *  list.h
 *
 *  Full Name:
 *  Course section:
 *  Description of the program: list data structure containing the tasks in the system
 *  
 */
 
#include "process.h"

struct node {
    Process *process;
    int processState;
    int terminationState;
    int arrivalState;
    struct node *next;
};

// insert and delete operations.

//note Process *process = struct process *process
