//  Created by Ali Behfarnia on 11/02/24.

// This code addresses two things: 1) Different between process ID and folk ID, and 2) zombie and orphant 

// Notes on Process Termination:
// 1. Process Termination and Exit Status: When a process finishes, it calls `exit()` and stops running, but its exit status remains.
// 2. Zombie State: The process enters a "zombie" state until the parent reads its exit status using `wait()` or `waitpid()`.
// 3. Releasing Memory: Once the status is collected, all memory and resources are fully released.
// 4. Orphan Processes:: If the parent has already exited, `init` adopts the process and cleans it up automatically.

// 5. waitpid(): is used to make the parent process wait for a specific child process


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* a[]) {
    int id = fork();

    if (id == 0) { // Child process
        printf("Child: getpid() = %d \n", getpid());
        printf("Child: fork id = %d \n", id);
        printf("Child (before sleep): current process ID %d, and parent ID: %d \n", getpid(), getppid());
        sleep(2);  // Delay child process
        printf("Child (after sleep): current process ID %d, and parent ID: %d \n", getpid(), getppid());
    } else {       // Parent process
        printf("Parent: getpid() = %d \n", getpid());
        printf("Parent: fork id = %d \n", id);
        printf("Parent: current process ID %d, and parent ID: %d \n", getpid(), getppid());
        sleep(1); // 
        exit(0);  // Terminate parent immediately
    }

    return 0;
}

// Result:

// Parent: getpid() = 89947 
// Parent: fork id = 89948 
// Parent: current process ID 89947, and parent ID: 77828 
// Child: getpid() = 89948 
// Child: fork id = 0 
// Child (before sleep): current process ID 89948, and parent ID: 89947 
// Child (after sleep): current process ID 89948, and parent ID: 1 


// ================ waitpid Example  

// int main(int argc, char* a[]) {
//     int id = fork();

//     if (id == 0) { // Child process
//         printf("Child: getpid() = %d \n", getpid());
//         printf("Child: fork id = %d \n", id);
//         sleep(2);  // Delay child process
//         printf("Child (after sleep): current process ID %d, and parent ID: %d \n", getpid(), getppid());
//     } else {       // Parent process
//         printf("Parent: getpid() = %d \n", getpid());
//         printf("Parent: fork id = %d \n", id);
//         printf("Parent: current process ID %d, and parent ID: %d \n", getpid(), getppid());
//         waitpid(id, NULL, 0);  // Wait for child process to finish
//         exit(0);  // Terminate parent immediately after waiting for the child
//     }

//     return 0;
// }


