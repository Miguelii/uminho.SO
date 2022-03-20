#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char* buffer[1024];

ssize_t readln(int fd, char *buffer, size_t size) {
    int i = 0;

    while( i < size && readc(fd, &buffer[i]) > 0) {
        i++;
        if (((char*)buffer)[i-1] == '\n') {
            return i;
        }
    }
    return i;
}

int readc(int fd,char *c) {
    return read(fd,c,1);
}