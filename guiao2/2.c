#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if(pid == 0) { //Filho
        printf("Pid Filho: %d, Pid Pai: %d \n", getpid(), getppid());
        _exit(0);
    }
    printf("Pid Pai: %d, Pid Pai do Pai: %d, Pid Filho: %d \n", getpid(),getppid(),pid);

    return 0;
}