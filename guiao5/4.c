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

    if(pipe(p) == -1) {
        perror("Erro no pipe");
        return -1;
    }

    pid_t pid;
    pid = fork();

    if(pid==0) {
        dup2(p[1],1);

        close(p[0]);
        close(p[1]);

        execlp("ls","ls","/etc",NULL);

        _exit(0);
    }

    dup2(p[0],0);

    close(p[0]);
    close(p[1]);

    execlp("wc","wc","-l",NULL);

    _exit(0);

    return 0;
}