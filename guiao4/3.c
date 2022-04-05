#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int main() {

    int outputOriginal = dup(1);

    int fd = open("/etc/passwd",O_RDONLY);
    dup2(fd,0);
    close(fd);

    int fd2 = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    dup2(fd2,1);
    close(fd2);

    int fd3 = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    dup2(fd3,2);
    close(fd3);

    
    dup2(outputOriginal,1);

    execlp("wc","wc",NULL);

    return 0;
}