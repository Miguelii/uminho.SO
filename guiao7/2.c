#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>



int main (int argc, char *argv[]) {
    int index = 3;

    for(int i = argc-3; i<=argc-3;i++) {
        pid_t pid;
        pid = fork();
        
        if(pid == 0) {
            int fd = open(argv[index],O_RDONLY);

            execlp("grep","grep",argv[2],fd,NULL);
            _exit(i);
        }
        index++;
    }

    for(int i = argc-3; i<=argc-3;i++) {
        int status;
        pid_t pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("Pid: %d, _exit: %d \n", pid, WEXITSTATUS(status));
        }
    }

    return 1;
}