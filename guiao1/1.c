#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* args[]) {
    int n;

    int fde = open("lista.txt", O_CREAT| O_TRUNC | O_WRONLY, 0666);
    if(fde == -1) perror("Erro no open");

    int fd = open("pessoas.txt", O_RDONLY);
    if(fd == -1) perror("Erro no open");

    char* buffer[1024];

    while((n = read(fd,buffer,1)) > 0) {
        write(fde,buffer,n);
    }

    close(fd);
    close(fde);

    return 0;
}