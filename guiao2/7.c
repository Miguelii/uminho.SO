#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

#define linhas 10
#define col 10

int matrix[linhas][col];
int linha[col];

void printmatrixBinaria() {
    int fd = open("matrix.txt", O_WRONLY);
    if(fd == -1) perror("Erro no open");

    lseek(fd,0,SEEK_SET);

    for(int i = 0; i < linhas; i++) {
        printf("%d",i);
    	for(int j = 0; j < col; j++) {

            lseek(fd,i*sizeof(linha),SEEK_SET);
            read(fd,&linha,sizeof(linha));

            printf("%d", linha[j]);
    	}
        printf("\n");
    }
}

int main() {
    pid_t pid;
    
    int num = 1;
    int res;
    int status;
    int ocorr = 0;
    
    int fd = open("matrix.txt", O_CREAT | O_RDWR, 0666);
    if(fd == -1) perror("Erro no open");

    // criar matrix aleatória e escrever cada linha no ficheiro
    for(int i = 0; i < linhas; i++) {
    	for(int j = 0; j < col; j++) {
            linha[j] = rand()%col;
    	}
        write(fd,&linha,sizeof(linha));
    }
    

    // Executar em concorrencia
    for(int i=0; i<linhas; i++) {
        pid = fork();
        if(pid == 0) {

            lseek(fd,i*sizeof(linha),SEEK_SET);
            read(fd,&linha,sizeof(linha));

            for(int j=0;j<col;j++) {
                if(linha[j] == num) {
                    _exit(1);
                }
            }
            _exit(0);
        } 
    }
    
    //WIFEXITED(status) : returns true if the child terminated normally.
    //WEXITSTATUS(status) : returns the exit status of the child. This macro should be employed only if WIFEXITED returned true.
    for(int i=0; i<linhas; i++) {
        int status;
        pid_t pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("_exit: %d Linha: %d \n", WEXITSTATUS(status),i);
            if(WEXITSTATUS(status) == 1) ocorr++;
            
        }
    }
    
    printf("Ocorr: %d \n",ocorr);
    printmatrixBinaria();
    close(fd);

    return 0;
}