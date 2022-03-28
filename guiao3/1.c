#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char* args[]) {

    execlp("ls","ls","-l",NULL);
    //execlp("ls","coiso","-l",NULL);
    
    return 1;
}