#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>



int main(int argc, char *argv[]) {

    int p[2];
    char buffer[1024];
    int status;

    if(pipe(p) == -1) {
        perror("Erro no pipe");
        return -1;
    }

    pid_t pid;
    pid = fork();

    if(pid==0) {
        dup2(p[0],0);

        // fehcar o que nao é necessário
        close(p[0]);
        close(p[1]);

        execlp("wc","wc",NULL);

        _exit(0);
    }

    close(p[0]);

    int n;
    while((n = read(0,buffer,sizeof(buffer))) > 0) {
        write(p[1],buffer,n);
    }

    /*
    for(int i=1; i<argc;i++) {
        write(p[1],argv[i],sizeof(argv[i]));
        printf("[Pai] Escrevi %s to pipe \n",argv[i]);
    }
    */


    close(p[1]);
    wait(&status);
    printf("[Pai] Out of wait \n");

    return 0;
}