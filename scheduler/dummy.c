#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

int main(){

    int numberOfProcesses = 3;
    int values[3][4] = {
        {0, 4, 2, 0},
        {1, 6, 1, 2},
        {2, 8, 4, 3}
    };

    ///////////////////////////////////////

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
        newNode -> next = NULL;
        *(structs + i) = newNode;
    }

    struct node *head = NULL;
    struct node *tail = NULL;

    char *states[] = {"blocked", "ready", "running"};
    int timeToProcess = structs[0]->process->cpu_time;
    int burtsTime =  (int)(structs[0]->process->cpu_time * 0.5);
    int currentCycle = 0;

    int runtimer = burtsTime;
    int blocktimer;
    int stateid = 2; // 0 blocked, 2 running
    char state[10];
    strcpy(state, states[2]);

    char *cycleResults[3];

    struct node* current;
    int numberOfReadyProcesses = 0;
    int terminatedProcesses = 0;

    while(terminatedProcesses < numberOfProcesses){

        for(int i = 0; i < numberOfProcesses; i++){
            current = structs[i];
            if (current -> process -> arrival_time == currentCycle){
                current -> processState = 1;
                current -> arrivalState = 1;
            }
            if(current -> processState == 1){
                enqueue(&head, &tail, current);
            }
            if(current -> terminationState == 1){
                terminatedProcesses++;
            }
        }

        sprintf(cycleResults[structs[0]->process->pid], "%d:%s", structs[0]->process->pid, states[stateid]);

        if(stateid == 0){
            blocktimer--;
            if(blocktimer == 0){
                stateid = 2;
                runtimer = burtsTime;
            }
        }
        else if(stateid == 2){
            timeToProcess--;
            runtimer--;
            if(runtimer == 0){
                stateid = 0;
                blocktimer = structs[0]->process->io_time;
            }
        }
        printf("%d %s\n", currentCycle, cycleResults[0]);
        currentCycle++;
    }

    printf("done...");
}

