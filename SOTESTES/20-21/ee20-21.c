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


// Nao testei nenhum exercicio e o enunciado era confuso, não sei se tá certo!!

/*
2)
*/
int procura (char* palavra, char* ficheiro);

int substitui (char* palavra, char* palavra_nova, char* ficheiro) {

    int fd = open(ficheiro, O_RDWR);
    if (fd < 0) perror("Erro open");

    int offset = procura(palavra,ficheiro);

    lseek(fd,offset,SEEK_SET);

    int res = write(fd,palavra_nova,sizeof(palavra_nova));

    if(res >= 0) {
        printf("Inserido\n");
        return 0;

    } else {
        perror("Erro write");
        return 1;
    }
}


/*
3)
*/

int *pids = NULL;
int processos;

void siginthander(int signum) {

    sleep(30);

    for(int i=0; i<processos;i++) {
        kill(pids[i],SIGKILL);
    }

    _exit(0);

}


int main(int argc, char* argv[]) {


    signal(SIGINT, siginthander);

    for(int i=1; i<=argc-3; i++) {
        pid_t pid;
        pid = fork();

        int res;
        
        if(pid==0) {
            res = substitui(argv[1],argv[2],argv[2+i]);

            if(res == 0) write(1,argv[2+i]);
        } else {
            pids[processos++] = pid;
        }
    }

    for(int i=1; i<argc-3; i++) {
        int status;
        pid_t pid = wait(&status);
    }

}

