#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {

    int fifo = open("fifo",O_RDONLY);
    if (fifo < 0) perror("Erro fifo");

    int leitura = 0;
    char buffer[1024];
    
    while((leitura = read(fifo,buffer,sizeof(buffer))) > 0) {
        write(1,buffer,leitura);
    }

    close(fifo);

    unlink("fifo");

    return 0;
}