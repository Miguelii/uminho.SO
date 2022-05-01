#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

// pipe[i][0] -> leitura
// pipe[i][1] -> Escrita

int main(int argc, char *argv[]) {
    int pipe_fd[3][2];
    int status;

    if(pipe(pipe_fd[0]) < 0) {
        perror("pipe");
        exit(1);
    }

    if(fork() == 0) {
        close(pipe_fd[0][0]);
        dup2(pipe_fd[0][1], 1);
        close(pipe_fd[0][1]);
        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
        _exit(1);
    }
    wait(&status);

    close(pipe_fd[0][1]);

    if(pipe(pipe_fd[1]) < 0) {
        perror("pipe");
        exit(1);
    }
    
    if (fork() == 0) {
        close(pipe_fd[1][0]);

        dup2(pipe_fd[0][0], 0);
        close(pipe_fd[0][0]);
        dup2(pipe_fd[1][1], 1);
        close(pipe_fd[1][1]);
        execlp("cut", "cut", "-f7", "-d:", NULL);
        _exit(1);
    }
    wait(&status);
    
    close(pipe_fd[0][0]);
    close(pipe_fd[1][1]);

    if(pipe(pipe_fd[2]) < 0) {
        perror("pipe");
        exit(1);
    }
    
    if (fork() == 0) {
        close(pipe_fd[2][0]);

        dup2(pipe_fd[1][0], 0);
        close(pipe_fd[1][0]);
        dup2(pipe_fd[2][1], 1);
        close(pipe_fd[2][1]);
        execlp("uniq", "uniq", NULL);
        _exit(1);
    }
    wait(&status);

    close(pipe_fd[1][0]);
    close(pipe_fd[2][1]);

    if (fork() == 0) {
        dup2(pipe_fd[2][0], 0);
        close(pipe_fd[2][0]);
        execlp("wc", "wc", "-l", NULL);
        _exit(1);
    }
    wait(&status);

    close(pipe_fd[2][0]);


    
    return 0;

}