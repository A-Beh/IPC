//  Created by Ali Behfarnia on 11/01/24.

// Waiting():
// Here, running the child and parent processes in parallel are practiced
// Example, numbers 1-5 are printed by the child process,and 6-10 are printed by the parent.

#include<string.h>
#include <stdio.h>
#include<stdlib.h> // This library includes functions for memory allocation, process control, conversions, utility functions.
#include<unistd.h> // This library provides access to various POSIX (Portable Operating System Interface).


int main(int argc, const char * argv[]) {
    
    int id = fork();
    int n;
    
    // This is to determine the starting number of the child and the parent
    if (id == 0){
        n = 1;
    } else{
        n = 11;
    }
    
    if (id != 0){   // if main() comes, then ..
        wait(NULL); // This waits for any child process to finish and
    }
    
    for (int i=n ; i < n+10; i++){
        printf("%d ", i);
        fflush(stdout); // Immediate output, and useful in real-time applications
    }
    
    if (id != 0){
        printf("\n");
    }
    
    
    return 0;
}
