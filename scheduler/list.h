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
    int state;
    struct node *next;
};

// insert and delete operations.

//note Process *process = struct process *process
