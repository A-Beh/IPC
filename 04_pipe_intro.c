// Created by Ali Behfarnia on 11/03/24.

// pipe() function in C:
// It is a method of Inter-Process Communication (IPC) that allows data to be transferred between two processes.
// It provides a UNIDIRECTIONAL communication channel where one process can write data and the other process can read it.
// Pipes are primarily used for communication between a parent and its child processes.


// Notes:
// a. Unidirectional Communication: Pipes allow data to flow in one direction only.
// b. File Descriptors: The pipe() system call creates two file descriptors: one for reading and one for writing.
// c. FIFO: Data in pipes is accessed in a first-in, first-out manner.

// How it works:
// When you call pipe(), it returns an array of two file descriptors:
// 1. pipefd[0]: This is the read end of the pipe.
// 2. pipefd[1]: This is the write end of the pipe.

// Example below:
// parents write in pipefd[1], and the child reads it from pipefd[0].

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* a[]) {
    int pipefd[2];          // Array to hold pipe file descriptors
    char message[] = "Hello from parent!";
    char read_buffer[50];

    // Create a pipe; pipefd[0] is for read, and pipefd[1] is for write
    if (pipe(pipefd) == -1) { // if successful, it returns 0; and if unsuccessful, it returns -1
        printf("Error happend in pipe creation. \n");
        return 100;
    }

    // Fork to create a child process
    int pid = fork();

    if (pid == 0) {         // Child process
        close(pipefd[1]);   // Close the write end in the child
        read(pipefd[0], read_buffer, sizeof(read_buffer));
        printf("Child received: %s\n", read_buffer);
        close(pipefd[0]);   // Close the read end after reading

    } else {                // Parent process
        close(pipefd[0]);   // Close the read end in the parent
        write(pipefd[1], message, strlen(message) ); // Write the message to the pipe
        close(pipefd[1]);   // Close the write end after writing
        wait(NULL);         // Wait for child process to complete
    }

    return 0;
}

// Results:
// Child received: Hello from parent!
