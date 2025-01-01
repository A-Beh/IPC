// Ali Behfarnia 11/2024

// Communication between processes using signals

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

// Signal handler for the child process to start working
void handle_sigusr1(int sig) {
    printf("Child: Received SIGUSR1 from parent. Starting work...\n");
    sleep(2);     // Simulate some work with a sleep
    printf("Child: Work done. Sending SIGUSR2 to parent.\n");
    kill(getppid(), SIGUSR2); // Send SIGUSR2 to parent
}

// Signal handler for the parent process to acknowledge child completion
void handle_sigusr2(int sig) {
    printf("Parent: Received SIGUSR2 from child. Acknowledging completion.\n");
}

int main(int aa, char* hh[]) {
    pid_t pid = fork(); // Create a child process

    if (pid == 0) {
        // Child process
        // Set up signal handler for SIGUSR1
        signal(SIGUSR1, handle_sigusr1);
        printf("Child: Waiting for SIGUSR1 from parent...\n");

        // Wait indefinitely until signal is received
        while (1) {
            pause(); // Wait for a signal to be delivered
        }
    } else {
        // Parent process
        // Set up signal handler for SIGUSR2
        signal(SIGUSR2, handle_sigusr2);
        printf("Parent: Sending SIGUSR1 to child to start work.\n");

        // Send SIGUSR1 to child to instruct it to start work
        kill(pid, SIGUSR1);

        // Wait for SIGUSR2 from the child process
        pause(); // Wait for a signal to be delivered
        printf("Parent: Child process has completed its work.\n");
    }

    return 0;
}

// Results:
// Parent: Sending SIGUSR1 to child to start work.
// Child: Waiting for SIGUSR1 from parent...
// Child: Received SIGUSR1 from parent. Starting work...
// Child: Work done. Sending SIGUSR2 to parent.
// Parent: Received SIGUSR2 from child. Acknowledging completion.
// Parent: Child process has completed its work.
