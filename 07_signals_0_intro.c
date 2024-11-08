// Created by Ali Behfarnia on 11/24.

// Signals:
// In C, Signals are notifications sent to a process to indicate events.  
// Signals are interrupts that the OS or other processes sends to a process
// to inform it of various events, such as I/O, memory allocation, etc.

// Some common signals include:
// a. SIGKILL: Kill signal, which forcefully terminates a process.
// b. SIGSEGV: Segmentation fault, raised on invalid memory access.
// c. SIGINT: Interrupt signal (usually sent when the user presses Ctrl + C).
// d. SIGCHLD: Sent to a parent process when a child process terminates.
// e. SIGTERM: Termination signal, which can be used to request the termination of a process.




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>


int main(int aa, char* hh[]) {
    int id = fork();
    
    if (id  == 0){
        while(1){
            printf("Something running: \n");
            sleep(0.99);
        }
        
    }else{
        sleep(1);
        kill(id, SIGKILL); // Note: the id here is the id of the child process.
        // To get the id of the parent process, we should use getpid()
        wait(NULL);
    }
    return 1;
}

// Results:
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
