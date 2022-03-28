#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char* args[]) {

    pid_t pid;
    pid = fork();

    if(pid == 0) {
        execlp("ls", "ls","-l",NULL);
        _exit(0);
    }
    int status;
    wait(&status);
    
    if(WIFEXITED(status)) {
        printf("_exit: %d \n", WEXITSTATUS(status));
    }

    return 0;
}