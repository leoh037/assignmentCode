

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
                    current->terminationState = 1;
                    current->turnaroundTime = currentCycle - current->process->arrival_time + 1;