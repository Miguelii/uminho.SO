#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/wait.h>

/*
Suponha que um professor pretende deixar de publicar no Blackboard as classificações dos alunos inscritos na sua UC,
passando a enviar por mail a cada um apenas a respectiva classificação. O referido professor já tem um ficheiro de texto
devidamente formatado com <aluno> <nota>, 10 caracteres por linha, e quer agora evitar o trabalho de enviar manualmente
centenas de mails! Veja o exemplo seguinte:
$ mail -s Sistemas_Operativos a00000@alunos.uminho.pt a00000 18
<ctrl-D>
Escreva um programa em C que leia linhas do ficheiro (passado como argumento) com os pares <aluno><nota> e envie
o respectivo email, executando o comando mail como exemplificado acima. Espera-se uma solução concorrente mas
limitando a concorrência a não mais de 10 processos simultâneos de mail.
*/


int main(int argc, char *argv[]) {


    if(strcmp(argv[1],"mail") == 0) {

        int buffer[1024];
        int fd = open("notas.txt", O_RDONLY);
        if(fd == -1) perror("Erro no open");


        
        /*
        //Concorrencia
        for(int i = 0; i<10;i++) {
            pid = fork();
            if(pid == 0) {

            }
        }
        */



    }
}