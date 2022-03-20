#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

typedef struct pessoa {
    char nome[200];
    int idade; 
}Pessoa;


int main (int argc, char *argv[]) {
    Pessoa p;
    int pos = 0;
    int fd;
    if (argc < 5) {
        perror("Erro: Nao foram inseridos argumentos suficientes na linha de comandos.\n");
        return 0;
    }

    if(strcmp(argv[2],"-i") == 0) {
        int res;

        strcpy(p.nome,argv[3]);
        p.idade = atoi(argv[4]);

        fd = open("pessoas.txt", O_CREAT | O_APPEND | O_WRONLY, 0666);
        if(fd == -1) perror("Erro no open");

        res = write(fd,&p,sizeof(Pessoa));

        //index of most recent entry (Nao faço ideia como é que isto funcemina)
        struct stat st;
        fstat(fd,&st);
        off_t filesize = st.st_size;
        pos = (int)filesize / sizeof(Pessoa);

        if(res >= 0) {
            printf("Inserido na Posição: %d \n", pos);
        }
        else{
            perror("Erro no write");
        }

        close(fd);
    }

    if(strcmp(argv[2],"-u") == 0) {
        int res;
        fd = open("pessoas.txt", O_RDWR);
        if(fd == -1) perror("Erro no open");
        int output = 0;

        while(read(fd,&p,sizeof(Pessoa)) > 0) {

            if(strcmp(p.nome,argv[3]) == 0) {

                lseek(fd,-sizeof(Pessoa),SEEK_CUR);

                p.idade = atoi(argv[4]);

                res = write(fd,&p,sizeof(Pessoa));

                if(res >= 0) {
                    printf("Inserido");
                    output = 1;
                }
                else {
                    perror("Erro no write");
                }

                close(fd);
            }
        }
        if(output == 0) perror("Erro no while");
 
    }

    if(strcmp(argv[2],"-o") == 0) {

        int res;
        fd = open("pessoas.txt", O_RDWR);
        if(fd == -1) perror("Erro no open");

        int posicao = atoi(argv[3]);

        // encontrar a posicao
        //lseek(fd,sizeof(struct pessoa) * posicao,SEEK_SET);

        lseek(fd, sizeof(struct pessoa) * (atoi(argv[3]) - 1), SEEK_SET);
        

        int fde = read(fd,&p,sizeof(struct pessoa));
        if(fde<0) perror("Erro no read");

        lseek(fd, sizeof(struct pessoa) * (atoi(argv[3]) - 1), SEEK_SET);

        p.idade = atoi(argv[4]);

        //lseek(fd,sizeof(p),SEEK_CUR);

        res = write(fd,&p,sizeof(p));
        if(res >= 0) {
            printf("Inserido");
            
        }
        else{
            perror("Erro no write");
        }
        close(fd); 
        }

        if(strcmp(argv[2],"-h") == 0) {
            ssize_t res;
            char idString[20];

            fd = open("pessoas.txt", O_RDONLY);

            while((res = read(fd,&p,sizeof(Pessoa))) > 0) {
                printf("%s - %d \n", p.nome,p.idade);
            }
            close(fd);
        }
}