// Ali Behfarnia 11/2024

// Signal Handler
// The signal handler is a function designed to specify what action a process should take when it receives a specific signal. 
// Without defining a custom signal handler, a process would handle signals using the default behavior defined by 
// the system, which may not always match your intended outcome.

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

// Signal handler function for the child process
void handle_sigterm(int sig) {
    printf("Child process received SIGTERM. Exiting...\n");
    _exit(0);
    // In C, _exit(0) is a function used to terminate a process immediately without performing any cleanup tasks, such as flushing open file buffers or calling
}

int main(int aa, char* hh[]) {

    pid_t pid = fork(); // Create a child process
    
    if (pid == 0) {
        signal(SIGTERM, handle_sigterm); // Set up signal handler for SIGTERM
        printf("Child process (PID: %d) is running.\n", getpid());
        
        while (1) {
            printf("Child process is working...\n");
            sleep(1);  // Simulate some work
        }
    }else {
        printf("Parent process (PID: %d) created child (PID: %d).\n", getpid(), pid);

        sleep(5);        // Let the child process run for a few seconds

        // Send SIGTERM to the child process to terminate it
        printf("Parent process sending SIGTERM to child process.\n");
        kill(pid, SIGTERM);

        // Wait for a moment to see the child process exit
        sleep(1);
        printf("Parent process done.\n");
    }


    return 1;
}

// Result:
// Parent process (PID: <parent_pid>) created child (PID: <child_pid>).
// Child process (PID: <child_pid>) is running.
// Child process is working...
// Child process is working...
// Child process is working...
// Child process is working...
// Child process is working...
// Parent process sending SIGTERM to child process.
// Child process received SIGTERM. Exiting...
// Parent process done.