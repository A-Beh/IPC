// Created by Ali Behfarnia on 11/24.

// Example of pipe: Summation in two processes

// An array is divided to two part, the sum of each part is obtained,
// then one process send the results into another process
// E.g., child process cal and write the sum, put it into the pipe,
// the other process (parent) read it

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    int arr[] = {10, 20, 50, 12, 13, 22, 93};
    int arr_size = sizeof(arr)/sizeof(int);
    int sum = 0;
    int fd[2];
    int start, end;
    
    pipe(fd);
    if (pipe(fd)== -1){
        printf("An error happend in pipe creation!");
    }
    
    int id = fork();
    
    if(id == 0){
        start = 0;
        end = arr_size/2;
    }else{
        start = arr_size/2;
        end = arr_size;
    }
    
    int i;
    
    for(i=start; i<end; i++){
        sum += arr[i];
    }
    
    printf("The partial sum: %d \n", sum);
    
    
    if (id == 0){
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
    }else{
        int sum_of_child = 0;
        int total_sum = 0;
        close(fd[1]);
        read(fd[0], &sum_of_child, sizeof(sum_of_child));
        close(fd[0]);
        
        total_sum = sum_of_child + sum;
        printf("Total sum equals to: %d \n", total_sum);
        wait(NULL);
    }
    
    
    return 0;
}
