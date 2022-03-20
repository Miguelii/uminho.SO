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
    
    // Executar sequencialmente
    for(int i=1; i<=10; i++) {
        pid = fork();
        if(pid == 0) {
            printf("Filho %d => Pid Filho: %d, Pid Pai: %d \n", i, getpid(), getppid());
            _exit(i);
        }
        int status;
        pid_t pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("_exit: %d \n", WEXITSTATUS(status));
        }
    }

    return 0;
}