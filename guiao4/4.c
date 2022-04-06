#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int main(int argc, char* argv[]) {

    //redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...
    char ficheiroentrada[50];
    char ficheirosaida[50];

    int i;
    int index = 1;
    for(i=1;i<argc;i++) {

        if(strcmp(argv[i],"-i") == 0) {
            strcpy(ficheiroentrada,argv[i+1]);
            printf("%s \n",ficheiroentrada);
            index += 2;
        }

        if(strcmp(argv[i],"-o") == 0) {
            strcpy(ficheirosaida,argv[i+1]);
            printf("%s \n",ficheirosaida);
            index += 2;
        }
    }

    printf("%d",index);

    execvp(argv[index],&argv[index]);

    /*
    pid_t pid;
    pid = fork();

    if(pid == 0) {
        execvp(argv[i],&argv[i]);
    }
    */
    return 0;
}