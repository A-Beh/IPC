
// Created by Ali Behfarnia on 11/24.

// SIGSTOP and SIGCONT Signals: An Example
// These can help putting the processes into Background and Foreground 
// SIGSTOP can be considered as "cntrl+z" process in Background, 
// SIGCONT can be considered as "fg" for putting process Foreground.

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


int main(int aa, char* hh[]) {
    int id = fork();
        
    if (id  == 0){
        while(1){
            printf("Something running: \n");
            usleep(100000);
        }
    }else{
        kill(id, SIGSTOP);
        
        int tim;
        do{
            printf("Put your time(s) for execusion: ");
            scanf("%d",&tim);
            
            if(tim > 0){
                kill(id,SIGCONT);
                sleep(tim);
                kill(id, SIGSTOP);
            }
        }while(tim>0);
        
        kill(id, SIGKILL);
        wait(NULL);
    }
    return 1;
}

// Results:
// Put your time(s) for execusion: 1
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Something running: 
// Put your time(s) for execusion: -2