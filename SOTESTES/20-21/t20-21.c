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

    int pids[9];
    for(int i = 1; i<= 9; i++) {
        pids[i] = fork();

        if(pids[i] == 0) {

            //Assumimos que os ficheiros tem o nome de regiao_i, sendo i
            // o nr da regiao de 1 a 9
            char ficheiro[15];
            sprintf(ficheiro, "regiao_%d.txt",i);

            execlp("grep","grep",cidadao,ficheiro,NULL);
        }
    }
    
    int res = 1;

    for(int i = 1; i<= 9; i++) {
        int status;
        pid_t pid = wait(&status);

        if(WEXITSTATUS(status) == 0) {
            res = 0;

            for(int i = 0; i< 9; i++) {
                kill(pids[i],SIGKILL);
            }
        }
    }

    return res;

}





int main() {


    
    /*
    //2)
    
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