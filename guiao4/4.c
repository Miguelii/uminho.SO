#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>


int redir(char *buffer) {

    //printf("%s \n",buffer);
    char *buf[1024];

    char *token = strtok(buffer, " ");

    int i = 0;
    while (token != NULL) {
        buf[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    buf[i] = NULL;


    char ficheiroentrada[100];
    char ficheirosaida[100];

    // redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...

    if(strcmp(buf[0],"-i")) strcpy(ficheiroentrada,buf[1]);
    if(strcmp(buf[2],"-o")) strcpy(ficheirosaida,buf[3]);
    
    execvp(buf[4],&buf[4]);

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

    //redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...
    char buffer[1024];

    readln(buffer);


    redir(buffer);


    return 0;
}