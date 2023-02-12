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
    int processState; // 0 = blocked, 1 = ready, 2 = running
    int terminationState; // 0 = not terminated, 1 = terminated
    int turnaroundTime; // cycle at which process was terminated
    int arrivalState; // 0 = not arrived, 1 = arrived
    int queuedState; // 0 = not in queue, 1 = in queue
    int burstTime; // the number of cycles a process spends in a cpu burt
    int remainingTime; // keeps track of how many cycles the process has run for
    int runTimer; // keeps track of how many more cycles the process has run during a given cpu burts
    int blockTimer; // keeps track of how many more cycles the process must be blocked for during a given i/o burst
    struct node *next;
};


//note Process *process = struct process *process
