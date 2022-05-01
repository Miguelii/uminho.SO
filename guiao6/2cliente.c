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

    int fifo = open("fifo",O_WRONLY);
    if (fifo < 0) perror("Erro fifo");

    char buffer[100];
    
    int n;
    while((n = read(0,buffer,100)) > 0) {
        write(fifo,buffer,n);
    }

    close(fifo);

    return 0;
}


