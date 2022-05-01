#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char * argv[]) {

    int log;
    log = open("log.txt", O_CREAT | O_APPEND | O_WRONLY, 0666);

    if(mkfifo("fifo",0600) < 0) perror("Erro fifo");

    int fifo = open("fifo",O_RDONLY);
    if (fifo < 0) perror("Erro fifo");

    while(1) {
        int leitura = 0;
        char buffer[1024];
    
        while((leitura = read(fifo,buffer,sizeof(buffer))) > 0) {
            write(log,buffer,leitura);
        }
    }

    //unlink("fifo");
        
}