#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#define BUFFER_SIZE 42

void criarFifo(char *str)
{
    if (mkfifo(str, 0666) == -1)
        printf("Erro na criação de pipe\n");
    else
        printf("FIFO %s criado com sucesso!\n", str);
}

int roud10(char *str)
{
    return str[6] == '1' && str[7] == '0'? 0 : 1;
}
void ler(char *name_r, char *name_w, int i)
{
    int fd;
    int fd_w;
    char buffer[BUFFER_SIZE];
    char str_tem[BUFFER_SIZE];

    fd_w = open(name_w, O_WRONLY);
    fd = open(name_r, O_RDONLY);
    
    do
    {
        read(fd, buffer, BUFFER_SIZE - 1);
        buffer[40] = '\0';

        if (strcmp(buffer, str_tem))
            printf("Msg: %s\n", buffer);
        strcpy(buffer, str_tem);

    } while (roud10(buffer));
    printf("Corrida terminou para carro numero %i\n", i);
    close(fd);
    close(fd_w);
}


int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    // abrir o FIFO para leitura
    //…
    // ler mensagem do FIFO
    char comando[36];
    int input;
    char carroIn[50];
    char carroOut[50];

    printf("Qual o numero do carro?\n");
    scanf("%i", &input);
    sprintf(carroIn, "CARRO%i.in", input);
    sprintf(carroOut, "CARRO%i.out", input);

    criarFifo(carroOut);
    criarFifo(carroIn);
    if (argc >= 2)
    {
        sprintf (comando, "/bin/bash ./testscript.sh %s &", argv[1]);
        system(comando);
    }
    ler(carroIn, carroOut, input);

}