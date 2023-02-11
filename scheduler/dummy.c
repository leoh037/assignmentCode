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

    struct node **arr = malloc(numberOfProcesses * sizeof(struct node*));   //will allocate a buffer big enough to hold n pointers struct nodes

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
        newNode -> state = 0;
        newNode -> next = NULL;
        *(arr + i) = newNode;
    }

    struct node *head = NULL;
    struct node *tail = NULL;

    char *states[] = {"blocked", "ready", "running"};
    int timeToProcess = arr[0]->process->cpu_time;
    int burtsTime =  (int)(arr[0]->process->cpu_time * 0.5);
    int cycle = 0;

    int runtimer = burtsTime;
    int blocktimer;
    int stateid = 2; // 0 blocked, 2 running
    char state[10];
    strcpy(state, states[2]);

    char *cycleResults[3];

    while(timeToProcess > 0){
        sprintf(cycleResults[arr[0]->process->pid], "%d:%s", arr[0]->process->pid, states[stateid]);
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
                blocktimer = arr[0]->process->io_time;
            }
        }
        printf("%d %s\n", cycle, cycleResults[0]);
        cycle++;
    }

    //this is a test

    printf("done...");
}

