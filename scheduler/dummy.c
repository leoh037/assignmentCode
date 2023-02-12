#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "queue.h"

int main(){

    int numberOfProcesses = 2;

    int values[3][4] = {
        {0, 2, 2, 0},
        {1, 2, 1, 2}
    };
    
    // int values[3][4] = {
    //     {0, 4, 2, 0},
    //     {1, 6, 1, 2},
    //     {2, 8, 4, 3}
    // };

    // int values[3][4] = {
    //     {0, 2, 2, 0}
    // };

    ///////////////////////////////////////

    printf("running dummy...\n");

    struct node **structs = malloc(numberOfProcesses * sizeof(struct node*));   //will allocate a buffer big enough to hold n pointers to struct nodes

    Process *process;
    struct node *newNode;

    for(int i = 0; i < numberOfProcesses; i++){
        process = malloc(sizeof(Process));
        process->pid = values[i][0];
        process->cpu_time = values[i][1];
        process->io_time = values[i][2];
        process->arrival_time = values[i][3];
        newNode = malloc(sizeof(struct node));
        newNode->process = process;
        newNode->processState = 0;
        newNode->terminationState = 0;
        newNode->arrivalState = 0;
        newNode->queuedState = 0;
        newNode->burstTime = round((process ->cpu_time) * 0.5);
        newNode->remainingTime = process -> cpu_time;
        newNode->runTimer = newNode -> burstTime;
        newNode->next = NULL;
        *(structs + i) = newNode;
    }

    struct node *head = NULL;
    struct node *tail = NULL;

    char *states[] = {"blocked", "ready", "running"};
    
    char* cycleResult;
    char overallResult[50];
    int shortestTime = 0;

    struct node* current;
    struct node* shortest;
    int numberOfReadyProcesses = 0;
    int terminatedProcesses = 0;
    int waitingProcesses = 0;
    int currentCycle = 0;
    int cpuCycles = 0;
    while(terminatedProcesses < numberOfProcesses){

        //go through the pointer to struct node array and examine on the state of all processes
        for(int i = 0; i < numberOfProcesses; i++){
            current = structs[i];            
            if (current->process -> arrival_time == currentCycle){
                current->processState = 1;
                current->arrivalState = 1;
                waitingProcesses++;
            }

            //find the process with the shortest remaining cpu time (note that here we are limiting our queue to having only one process in a cycle)
            if((current->terminationState != 1) && (current->processState == 1) && (current->queuedState == 0) && (getSize(&head) == 0)){
                if( shortestTime == 0){
                    shortest = current;
                }
                else{
                    if(current->remainingTime < shortestTime){
                        shortest = current;
                    }
                }

                shortestTime = shortest->remainingTime;

                if((i + 1) == numberOfProcesses){
                    printf("shortest time = %d\n", shortest->remainingTime);
                    enqueue(&head, &tail, shortest);
                    shortest->queuedState = 1;
                    shortest->processState = 2;
                    shortestTime = 0;
                    printf("current on queue = %d\n", shortest->process->pid);
                }
            }
        }
        printf("queue size cycle %d is = %d\n", currentCycle, getSize(&head));

        //ensure that only the process at the head of the queue is in a running state, all other processes in the queue are ready, and those not on the queue are either blocked or have terminated
        if(getSize(&head) > 0){
            if(head -> processState != 2){
                head -> processState = 2;
            }
        }

        // do the following for every process that has arrived and is not in a ready state

        sprintf(overallResult, "%d ", currentCycle);

        for(int i = 0; i < numberOfProcesses; i++){
            current = structs[i];
            cycleResult = malloc(10 * sizeof(char));
            if((current -> arrivalState == 1) && (current->terminationState != 1)){
                
                sprintf(cycleResult, "%d:%s ", current->process->pid, states[current->processState]);

                if(current->processState == 0){
                    (current->blockTimer) = (current->blockTimer) - 1;
                    if(current -> blockTimer == 0){
                        //set to ready state
                        current->processState = 1;
                        current->runTimer = current->burstTime;
                    }
                }
                else if(current->processState == 2){
                    current->remainingTime = current->remainingTime - 1;
                    current->runTimer = current -> runTimer - 1;
                    if(current -> runTimer == 0){
                        //set process to blocked stated
                        current->processState = 0;
                        dequeue(&head);
                        current->queuedState = 0;
                        current->blockTimer = current->process->io_time;
                    }
                    cpuCycles++;
                }
                if(current->remainingTime == 0){
                    dequeue(&head);
                    current->terminationState = 1;
                    current->turnaroundTime = currentCycle - current->process->arrival_time + 1;
                    terminatedProcesses++;
                    waitingProcesses--;
                }
            }
            else{
                cycleResult = "";
            }
            strcat(overallResult, cycleResult);
        }
        //printf("%s\n", overallResult);
        currentCycle++;
    }
    // printf("(empty line)\n");
    // printf("Finishing time: %d\n", currentCycle - 1);
    // printf("CPU utilization: %0.2f\n", (double)cpuCycles/currentCycle);
    // for(int i = 0; i<numberOfProcesses; i++){
    //     current = structs[i];
    //     printf("Turnaround process %d: %d\n", current->process->pid, current->turnaroundTime);
    // }
}

