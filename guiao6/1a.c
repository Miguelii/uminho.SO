#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){

    if(mkfifo("fifo",0600) < 0) perror("Erro fifo");

    //unlink("fifo");
}
