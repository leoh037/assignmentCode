/**
 *  list.c
 *
 *  Full Name:
 *  Course section:
 *  Description of the program: Various list operations
 *  
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "process.h"


// add a new node to the front of list 
void insert(struct node **pHead, Process *newProcess) {
    // add the new process to the list 
    struct node *newNode = malloc(sizeof(struct node));

    newNode->process = newProcess; // (*newNode).process = newProcess
    newNode->next = *pHead; // (*newNode).next = *pHead
    *pHead = newNode;
}

// delete the selected node from the list
void delete(struct node **pHead, Process *process) {
    struct node *currentNode;
    struct node *previousNode;

    currentNode = *pHead; //note: *pHead == head
    // special case - beginning of list
    if (process->pid == currentNode->process->pid) { /// (*process).pid == (*currentNode).(*process).pid
        *pHead = (*pHead)->next;
    }
    else {
        // interior or last element in the list
        previousNode = *pHead;
        currentNode = currentNode->next;
        while ((process->pid != currentNode->process->pid) ) {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }

        previousNode->next = currentNode->next;
    }
}

// traverse the list
void traverse(struct node *pHead) {
    struct node *currentNode;
    currentNode = pHead;

    while (currentNode != NULL) {
        printf("[%d] [%d]\n", currentNode->process->pid, currentNode->process->cpu_time);
        currentNode = currentNode->next;
    }
}
