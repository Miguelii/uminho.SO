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

int numeroFilhos = 0;
int *pids = NULL;

void child_handler(int signum) {
    if (pids == NULL) _exit(-1);

    for (int i = 0; i < numeroFilhos; i++) {
        kill(pids[i], SIGKILL);
    }
    _exit(0);
}

int main (int argc, char *argv[]) {
    
    int processos = argc-3;
    pids = (int *) malloc(sizeof(int) * processos);

    signal(SIGCHLD, child_handler);

    for(int i = 1; i<=argc-3;i++) {
        pid_t pid;
        pid = fork();
        
        if(pid == 0) {
            execlp("grep","grep",argv[2],argv[2+i],NULL);
        } else {
            pids[numeroFilhos++] = pid;
        }
    }

    
    return 0;
}