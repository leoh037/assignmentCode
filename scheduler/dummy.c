#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

int main(){

    // int numberOfProcesses = 3;
    // int values[3][4] = {
    //     {0, 4, 2, 0},
    //     {1, 6, 1, 2},
    //     {2, 8, 4, 3}
    // };

    int numberOfProcesses = 2;
    int values[2][4] = {
        {0, 4, 2, 0},
        {1, 6, 1, 2}
    };

    ///////////////////////////////////////

    printf("running dummy...")

    struct node **structs = malloc(numberOfProcesses * sizeof(struct node*));   //will allocate a buffer big enough to hold n pointers struct nodes

    Process *process;
    struct node *newNode;

    for(int i = 0; i < numberOfProcesses; i++){
        process = malloc(sizeof(Process));
        process->pid = values[i][0];
        process->cpu_time = values[i][1];
        process->io_time = values[i][2];
        process->arrival_time = values[i][3];
        newNode = malloc(sizeof(struct node));
        newNode -> process = process;
        newNode -> processState = 0;
        newNode -> terminationState = 0;
        newNode -> arrivalState = 0;
        newNode -> queuedState = 0;
        newNode -> burstTime = (int)(process -> cpu_time * 0.5);
        newNode -> remainingTime = process -> cpu_time;
        newNode -> runTimer = 0;
        newNode -> blockTimer = newNode -> burstTime;
        newNode -> next = NULL;
        *(structs + i) = newNode;
    }

    struct node *head = NULL;
    struct node *tail = NULL;

    char *states[] = {"blocked", "ready", "running"};
    int timeToProcess = structs[0]->process->cpu_time;
    int burtsTime;
    int currentCycle = 0;

    char state[10];
    strcpy(state, states[2]);

    char *cycleResults[2];

    struct node* current;
    int numberOfReadyProcesses = 0;
    int terminatedProcesses = 0;
    int waitingProcesses = 0;

    while(terminatedProcesses < numberOfProcesses){
    
        //go through the pointer to struct node array and examine on the state of all processes
        for(int i = 0; i < numberOfProcesses; i++){
            current = structs[i];
            if (current -> process -> arrival_time == currentCycle){
                current -> processState = 1;
                current -> arrivalState = 1;
                waitingProcesses++;
            }
            if((current -> processState == 1) && (current -> queuedState == 0)){
                enqueue(&head, &tail, current);
                current -> queuedState = 1;
            }
            if(current -> terminationState == 1){
                terminatedProcesses++;
                waitingProcesses--;
            }
        }
        //ensure that only the process at the head of the queue is in a running state, all other processes in the queue are ready, and those not on the queue are either blocked or have terminated
        if(getSize(&head) > 0){
            if(head -> processState != 2){
                head -> processState = 2;
            }
        }
        // do the following for every process that has arrived and is not in a ready state
        for(int i = 0; i < numberOfProcesses; i++){
            current = structs[i];
            
            if(current -> terminationState != 1){
                sprintf(cycleResults[current->process->pid], "%d:%s", current->process->pid, states[current -> processState]);
                if(current -> processState == 0){
                    current -> blockTimer = current -> blockTimer - 1;
                    if(current -> blockTimer == 0){
                        //set to ready state
                        current -> processState = 1;
                        current -> runTimer = current -> burstTime;
                    }
                }
                else if(current -> processState == 2){
                    current -> remainingTime = current ->remainingTime - 1;
                    current -> runTimer = current -> runTimer - 1;
                    if(current -> runTimer == 0){
                        //set process to blocked stated
                        current -> processState = 0;
                        Dequeue(&head);
                        current -> blockTimer = current -> process -> io_time;
                    }
                }
                if(current -> remainingTime == 0){
                    current -> terminationState = 1;
                }
            }
        }
        //print out all the analytics for waiting processes in a for loop
        printf("%d %s %s\n", currentCycle, cycleResults[0], cycleResults[1]);
        currentCycle++;
    }

    printf("done...");
}

