#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>


int mensagens(char *palavra, char *ficheiro) {

    int p[2];

    if(pipe(p) < 0) {
        perror("pipe");
        exit(1);
    }
    
    pid_t pid;
    int status;

    if(fork()==0) {
        dup2(p[1],1);
        close(p[0]);
        close(p[1]);

        
        execlp("grep","grep",palavra,ficheiro,NULL);
        _exit(1);
    }
    wait(&status);

    close(p[1]);

    if(fork()==0) {
        dup2(p[0],0);
        close(p[0]);
        close(p[1]);

        execlp("wc","wc","-l",NULL);
        _exit(1);
    }
    wait(&status);

    close(p[0]);

    // Falta dar return ao numero que aparece no stdout...

    return 0;
}



int main() {


    char *filePath = "regiao_1.txt";
 
    mensagens("Manuel",filePath);

    return 0;
}