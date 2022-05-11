#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

int ctrl_c_counter = 0;
int seconds = 0;

void sigint_handler (int signum) {
    printf("sigint received code %d\n",signum);
    //tempo passado
    printf("execution time: %d\n",seconds);
    ctrl_c_counter ++;
}

void sigquit_handler (int signum) {
    printf("sigquit received code %d\n",signum);
    printf("ctrl + c counter: %d",ctrl_c_counter);
    exit(0);
}

void sigalarm_handler (int signum){
    printf("alarm signal received code: %d\n",signum);
    seconds ++;
    alarm(1);

}

int main (int argc, char *argv[]){
    if (signal(SIGINT, sigint_handler) == SIG_ERR){
        perror("signal sigint");
        exit(1);
    }

    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR){
        perror("signal sigkill");
        exit(1);
    }

    if (signal(SIGALRM,sigalarm_handler) == SIG_ERR){
        perror("signal sigalrm");
        exit(1);
    }

    alarm(1);
    while(1){

        pause();
        printf("interrupted \n");
    }

    return 0;
}