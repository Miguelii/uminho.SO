#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int mySystem(char *comand) {

    char *buf[1024];

    char *aux = strdup(comand);

    char *token = strtok(aux, " ");

    int ind=0;
    while (token != NULL) {
        buf[ind] = token;
        ind++;
        token = strtok(NULL, " ");
    }
    buf[ind] = NULL;


    //printf("Debug: %s \n", buf[0]);
    //printf("Debug: %s \n", buf[1]);
    //printf("Debug: %s \n", buf[2]);

    pid_t pid;

    // Executar em concorrencia
    for(int i=0; i<3; i++) {
        pid = fork();
        if(pid == 0) {
            execvp(buf[i],&buf[i]);
            _exit(i);
        }
    }

    for(int i=0; i<3; i++) {
        int status;
        pid_t pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("Pid: %d, _exit: %d \n", pid, WEXITSTATUS(status));
        }
    }

    return 0;
}

ssize_t readln(char *line) {
	ssize_t res = 0;
	ssize_t i = 0;
    
	while ((res = read(0, &line[i], 1)) > 0 && ((char) line[i] != '\n')) {
		i+=res;
	}
    line[i] = '\0';

	return i;
}

int main(int argc, char* argv[]) {

    char acao[1024];
    readln(acao);
    //printf("%s \n",acao);
    mySystem(acao);
    return 0;

}