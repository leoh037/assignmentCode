/**
 *  scheduler.c
 *
 *  Full Name:
 *  Course section:
 *  Description of the program:
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "scheduler.h"
#include "process.h"

#define SIZE    100

int main(int argc, char *argv[])
{
	FILE *fp;

	int num_of_processes;

	fp  = fopen(argv[1],"r");

	fscanf(fp, "%d", &num_of_processes);    
	
	if (num_of_processes > 0){
		Process *queue = malloc(num_of_processes * sizeof(Process));      

		for (int i=0; i<num_of_processes; i++){
			fscanf(fp, "%d %d %d %d",
					&queue[i].pid, 
					&queue[i].cpu_time, 
					&queue[i].io_time, 
					&queue[i].arrival_time); 
		}                                                                               

		for(int i =0; i<num_of_processes; i++) {
			printf("A: %d B: %d  C: %d D: %d \n",
					queue[i].pid, 
					queue[i].cpu_time, 
					queue[i].io_time, 
					queue[i].arrival_time);    
		}
		free(queue); 
	}

	fclose(fp);


	return 0;
}
