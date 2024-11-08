// Created by Ali Behfarnia on 11/24.

// Two pipe - two way communication:

// Below Example:
// One pipe is defined for sending data from the parent to the child.
// One pipe is defined for sending data from the child to the parent.



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>


int main(int argc, const char * argv[]){
    int pipe1[2]; // Parent to child (so child only reads)
    int pipe2[2]; // Child to parent (so child only writes)
    
    // Check for pipe creation errors
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) { 
        return 100;
    }
    
    int id = fork();
    if (id == -1) { 
        return 101; // check if there's an error in forking
    }

    if (id == 0) { // Child process
        close(pipe1[1]); // Close unused write end of pipe1
        close(pipe2[0]); // Close unused read end of pipe2

        int x;
        read(pipe1[0], &x, sizeof(x)); // Read data sent from the parent
        printf("Child received %d done!\n", x);
        
        x *= 5; // Modify the data
        printf("Child multiplication is done! Writing %d.\n", x);
        
        write(pipe2[1], &x, sizeof(x)); // Send modified data back to parent
        printf("Writing %d done in the child process\n", x);

        // Close the pipe ends used in the child
        close(pipe1[0]);
        close(pipe2[1]);
    } else { // Parent process
        close(pipe1[0]); // Close unused read end of pipe1
        close(pipe2[1]); // Close unused write end of pipe2

        srand(time(NULL));
        int x0 = rand() % 10; // Generate random number
        write(pipe1[1], &x0, sizeof(x0)); // Send data to child
        printf("Parent writing %d done!\n", x0);
        
        wait(NULL); // Wait for child process to complete

        // Now read the modified data from the child
        read(pipe2[0], &x0, sizeof(x0));
        printf("Parent reading %d done!\n", x0);

        // Close the pipe ends used in the parent
        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}


// Result:
// Parent writing 8 done!
// Child received 8 done!
// Child multiplication is done! Writing 40.
// Writing 40 done in the child process
// Parent reading 40 done!