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

char ** parse_entry(char **position);

int server() {
    
    if(mkfifo("fifo",0600) < 0) perror("Erro fifo");

    int leitura = open("fifo", O_RDONLY);


    char buffer[1024];
    while (1) {

        while(read(leitura,buffer, sizeof(buffer)) >0 ) {

        }

    }



}




// 2)

int vacinados(char *regiao, int idade) {

    char idadeString[6];
    sprintf(idadeString, "%d", idade);

    int fd = open(regiao,O_WRONLY);
    if (fd == -1) perror("Erro no open");

    int p[2];
    if(pipe(p) == -1) perror("Erro no pipe");

    int status;

    pid_t pid;
    pid = fork();
    if(pid == 0) {
        
        dup2(p[1],1);
        close(p[0]);
        close(p[1]);

        execlp("grep","grep",idadeString,regiao,NULL);

        _exit(0);
    }
    wait(&status);

    dup2(p[0],0);
    close(p[0]);
    close(p[1]);

    execlp("wc","wc","-l",NULL);

    return 0;
}

// 3)

int vacinado(char* cidadao) {

    for(int i = 1; i<= 9; i++) {
        pid_t pid;
        pid = fork();

        if(pid == 0) {

            char ficheiro[15];
            sprintf(ficheiro, "regiao_%d.txt",i);

            execlp("grep","grep",cidadao, ficheiro,NULL);
            _exit(0);
        }
    }
    
    int res = 1;

    for(int i = 1; i<= 9; i++) {
        int status;
        pid_t pid = wait(&status);

        if(WIFEXITED(status) == 0) {
            res = 0;
        }
    }

    return res;

}





int main() {


    /*
    2)
    
    char *filePath = "regiao_1.txt";
    int idade = 60;

    vacinados(filePath,idade);
    */

    /*
    3)
    */

    char *cidadao = "Miguel";
    
    printf("EX3): %d \n", vacinado(cidadao));

    return 0;
}