#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

// $cat filename
// output: "Este texto está dentro do filename"

int main(int argc, char* args[]) {

    char* buffer[1024];

    //executar concorrenciax
    int n;
    while((n = read(STDIN_FILENO,buffer,1)) > 0) {
        write(STDOUT_FILENO,buffer,n);
    }
}