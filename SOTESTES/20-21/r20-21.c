#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>


// 1)


int main(int argc, char *argv[]) {

    pid_t pid;

    for(int i=1;i<=10;i++) {

        pid = fork();

        if(pid == 0) {

            execvp(argv[i], &argv[i]);
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

    close(p[1]);

    dup2(p[0],0);
    close(p[0]);

    execlp("cut","cut","-d"," ","-f4",NULL);

    return 0;
}

/*

// 3) INCOMPLETO

int seconds = 0;
int rondas = 0;
int *pids = NULL;

void sigalarm_handler (int signum){
    seconds ++; 
    alarm(1);
}

void sigint_handler (int signum) {

    printf("Rondas Finalizadas: %d\n",rondas);

    kill(getpid(),SIGKILL);

    exit(0);
}


int main() {

    if (signal(SIGALRM,sigalarm_handler) == SIG_ERR){
        perror("signal sigalrm");
        exit(1);
    }

    if (signal(SIGINT, sigint_handler) == SIG_ERR){
        perror("signal sigint");
        exit(1);
    }


    alarm(1);


    while(1) {

        int i;
        pid_t pid;
        for(i=1; i<100;i++) {
            pid=fork();

            if(pid == 0) {
                execlp("cmd","cmd",NULL);
            }
            int status;
            pid_t pid = wait(&status);

            if(seconds > 20) {
                kill(getpid(),SIGKILL);
                break; //acabar ronda se passar dos 20 segundos
            }
        }


        printf("Comando executou: %d vezes \n",i);

        if(i==100) {
            rondas++;
        }
    }

    


    return 0;

}

*/