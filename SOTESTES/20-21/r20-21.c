#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>



// 1)

int main(int argc, char *argv[]) {

    pid_t pid;

    for(int i=1;i<=10;i++) {

        pid = fork();

        if(pid == 0) {

            execvp(argv[1], &argv[2]);
        }
        int status;
        pid_t pid = wait(&status);

    }


    pid_t f;
    f = fork();

    int p[2];
    if(pipe(p) == -1) perror("Erro pipe");

    char procPidString[30];
    sprintf(procPidString, "/proc/%d/memstats", getpid());

    if(f==0) {

        dup2(p[1],1);
        close(p[0]);
        close(p[1]);

        execlp("grep","grep","VmPeak",procPidString,NULL);
    }

    dup2(p[0],0);
    close(p[0]);
    close(p[1]);

    execlp("cut","cut","-d"," ","-f4",NULL);

    return 0;
}