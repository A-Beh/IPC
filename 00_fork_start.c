//  Created by Ali Behfarnia on 11/5/24.

// fork()
// Purpose: It creates a new process (child) as a duplicate of the calling process (parent), enabling multiprocessing.
// Parallel Execution: Both parent and child can run concurrently, performing independent tasks.

// Notes:
//    a. It returns 0 for the child process.
//    b. Parent ID has a number.
//    c. if we put n fork(), it creates 2^n process, becasue it creates a new process for each generated process/node.

#include<string.h>
#include <stdio.h>
#include<stdlib.h> // This library includes functions for memory allocation, process control, conversions, utility functions.
#include<unistd.h> // This library provides access to various POSIX (Portable Operating System Interface).

int main(int argc, char* a[] ) {
    int id = fork();
    if (id != 0){
        fork();
    }
    
    printf("Hello, World from id: %d \n", id);
    if (id == 0) {
        printf("This is a child process \n");
    } else{
        printf("THis is the main process \n");
    }
    
    return 0;
}

// Result:
// Hello, World from id: 77518 
// THis is the main process 
// Hello, World from id: 0 
// This is a child process 
// Hello, World from id: 77518 
// THis is the main process 