// Created by Ali Behfarnia on 11/02/24.

// Multiple process creation, and wait for ALL childern finish the processes

// Note:
// wait(NULL) function only wait for one process to finish, whichever done sooner,
// this doesn't help when we have a parent that have in-depth (grand) childern

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


int main(int argc, char* a[]) {
    int id1 = fork();
    int id2 = fork();
    if (id1 == 0){
        if (id2 == 0){
            printf("This is the process B \n");
        }else{
            printf("This is process A \n");
        }
    
    }else{
        if (id2 ==0){
            printf("This is process C \n");
        }else{
            printf("This is parent proces \n");
        }
    }

//  errno: This is a global variable set by system calls and some library functions to indicate what error occurred. The value of errno is defined in errno.h. In this context, ECHILD is an error code that indicates there are no more child processes to wait for.
    while(wait(NULL) != -1 || errno != ECHILD){
        printf("waited for a child to finish processing. \n");
    }
        
    return 0;
}
