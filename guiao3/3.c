#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int main(int argc, char* argv[]) {

    pid_t pid;

    // Executar em concorrencia
    for(int i=1; i!=argc; i++) {
        pid = fork();
        if(pid == 0) {
            execlp(argv[i],argv[i],NULL);
            _exit(i);
        }
    }

    for(int i=1; i!=argc; i++) {
        int status;
        pid_t pid = wait(&status);
        if(WIFEXITED(status)) {
            //printf("Pid: %d, _exit: %d \n", pid, WEXITSTATUS(status));
        }
    }
}