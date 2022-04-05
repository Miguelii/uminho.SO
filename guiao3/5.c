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

    int i=0;
    while (token != NULL) {
        buf[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    buf[i] = NULL;

    int fundo = 0;
    if (strcmp(buf[i-1], "&") == 0)  {
        fundo = 1;
        i--;
    }
    buf[i] = NULL;

    //printf("Debug Fundo:: %d \n",fundo);
    //printf("Debug: %s \n", buf[0]);
    //printf("Debug: %s \n", buf[1]);

    pid_t pid;
    pid = fork();

    if(pid==0) {
        execvp(buf[0],buf);
        _exit(1);
    }

    int status;
    if(fundo == 0) wait(&status);

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

    while(1) {
        readln(acao);
        //printf("%s \n",acao);

        if (!strcmp(acao, "exit")) break;
        mySystem(acao);
    }
    
   
}