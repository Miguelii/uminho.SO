#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int pai2filho() {
    int p[2];   // p[0] -> Leitura   p[1] -> Escrita
    char *linhas[] = {"Linha1","Linha2","Linha3","Linha4"};
    char buffer; // Para ler caracter a caracter
    char buff[10]; // Para ler logo uma linha
    int status;
    int numLinhas = 4;

    if(pipe(p) == -1) {
        perror("Erro no pipe");
        return -1;
    }

    pid_t pid;
    pid = fork();

    if(pid==0) {

        close(p[1]);

        //Ler linhas até o read nao devolver 0 (EOF)
        //while(read(p[0],buffer,7) > 0) // ver linha a linha
        while(read(p[0],&buffer,1) > 0) { // ler caracter a caracter
            printf("[Filho] read -> %c From pipe \n", buffer);
        }
        
        printf("[Filho] Out of While \n");
        close(p[0]);
        _exit(0);
    }


    close(p[0]);
    for(int i = 0; i<numLinhas;i++) {
        write(p[1],linhas[i],strlen(linhas[i]));
        printf("[Pai] Escrevi %s to pipe \n",linhas[i]);
        sleep(5);
    }

    close(p[1]);
    wait(&status);
    printf("[Pai] Out of wait \n");

    return 0;
}

int main() {
    pai2filho();
}