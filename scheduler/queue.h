/**
 *  queue.c
 *
 *  Full Name:
 *  Course section:
 *  Description of the program: Various queue operations
 *  
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

//add a new node to the back of the queque (tail of the linked list)
void enqueue(struct node **pHead, struct node **pTail, struct node *newNode) {
    //if the queue is empty
    if(*pHead == NULL){
        *pHead = newNode;
        *pTail = newNode;
    } else{
        //if queue has at least one node in it
        (*pTail) -> next = newNode;
        *pTail = newNode;
    }
    newNode -> next = NULL;
    //printf("added process with id = %d to the queue\n", newNode->process->pid);
}

//remove a node from the front of the queue (head of the linked list)
struct node * dequeue(struct node **pHead){
    //only dequeue if the queue is not empty
    struct node *temp = *pHead;
    if(*pHead != NULL){
        *pHead = (*pHead) -> next;
        //printf("removed process with id = %d from the queue\n", temp->process->pid);
    }
    else{
        //printf("The queue is empty\n");
    }
    return temp;
}

//get the size of the queue
int getSize(struct node **pHead){
    int count = 0;
    if(*pHead != NULL){
        struct node *current = *pHead;
        while(current != NULL){
            current = current -> next;
            count++;
        }
    }
    return count;
}