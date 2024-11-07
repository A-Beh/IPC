
// Created by Ali Behfarnia on 11/24.

// FIFO:
// It is a method used to allow communication between processes. 
// FIFO can be used to create a named pipe, similar to a regular pipe, but with an important distinction:
// It has a name and can be accessed by unrelated processes (i.e., processes that do not share a parent-child relationship).
// FIFO provides a unidirectional communication channel, meaning that data flows in one direction from one process to another.

// Steps to use it:
// 1. creation of a file: we use mkfifo() to create a named FIFO. (or simply mkfile in dir folder).
// 2. opening of a file: Both processes open the FIFO using open(). The writer opens it for writing (O_WRONLY), and the reader opens it for reading (O_RDONLY).
// 3. Write: The writer process writes data to the FIFO using write().
// 4. Read: The reader process reads from the FIFO using read().
// 5. close: Once the communication is done, both processes close the FIFO file using close().

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>


int main(int argc, const char * argv[]) {
    
    int arr[5];
    int fd_r = open("sum", O_RDONLY);
    if (fd_r == -1){
        printf("Error occured in read only!");
    }

    for (int k ; k <5 ; k++){
        if (read(fd_r, &arr[k], sizeof(int)) == -1){
            printf("Error occured in loop read!");
        }
        printf("Finished receiving %d \n", arr[k]);
    }

    close(fd_r);

    return 0;
}

// Result:
// Finished receiving 6 
// Finished receiving 3 
// Finished receiving 5 
// Finished receiving 1 
// Finished receiving 2 