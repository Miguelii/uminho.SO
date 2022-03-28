#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

#define linhas 5
#define col 10

int matrix[linhas][col];

void printmatrix() {
    for(int i = 0; i < linhas; i++) {
    	for(int j = 0; j < col; j++) {
            printf("%d", matrix[i][j]);
    	}
        printf("\n");
    }
}

int main() {
    pid_t pid;
    
    int num = 1; //numero a procurar
    int ocorr = 0;

    // Pedido do stor
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < col; j++) {
            matrix[i][j] = 0;
    	}
    }  
    matrix[0][9] = 1;
    matrix[1][5] = 1;
    matrix[3][0] = 1;
    
    /*
    // criar matrix aleatória
    for(int i = 0; i < linhas; i++) {
    	for(int j = 0; j < col; j++) {
            matrix[i][j] = rand()%col;
    	}
    }
    */
    int arr[linhas];
    int aux[linhas];

    // Executar em concorrencia
    for(int i=0; i<linhas; i++) {
        pid = fork();
        arr[i] = pid;
        if(pid == 0) {
            //percorrer as colunas da matrix até encontrar o numero
            for(int j=0;j<col;j++) {
                if(matrix[i][j] == num) {
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
            if(WEXITSTATUS(status) == 1) {
                ocorr++;
                for(int j=0;j<linhas;j++) {
                    if(arr[j] == pid) printf("Linha: %d Pid: %d \n",j,pid); 
                    /*
                    char str[256];
                    snprintf(str,sizeof(str),"%d",i);
                    write(1,str,sizeof(str));
                    */
                }
            }

        }
    }
    
    printf("Ocorr: %d \n",ocorr);
    printmatrix();
    for(int i=0;i<linhas;i++) printf("Array: %d \n",arr[i]);

    return 0;
}