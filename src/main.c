#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#define BUFFER_SIZE 20
#define FIFO_PATH "fifo1"

void criarFifo(char *str)
{
    if (mkfifo(str, 0666) == -1)
        printf("Erro na criação de pipe\n");
    else
        printf("FIFO %s criado com sucesso\n", str);
}

void ler(char *nameFile, char *buffer)
{
    int size;
    int fd;
    fd = open(nameFile, O_RDONLY);
    while((size = read(fd, buffer, sizeof(buffer)))> 0)
    {
        write(STDIN_FILENO, buffer, size);
    }
    close(fd);
}

void escrever(char *nameFile, char *msg)
{
    int fd;
    fd = open(nameFile, O_WRONLY);
    write(fd, msg, sizeof(msg));
    close(fd);
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    // abrir o FIFO para leitura
    //…
    // ler mensagem do FIFO
    char comando[100];
    char buffer[BUFFER_SIZE];

    criarFifo("Carro.in");
    criarFifo("Carro.out");
    if (argc >= 2)
    {
        sprintf (comando, "/bin/bash ./testscript.sh %s &", argv[1]);
        system(comando);
    }
    escrever("Carro.out", "");
    ler("Carro.in", buffer);

}


/*
int main(int argc, char **argv)
{
    int input;
    char carroIn[50];
    char carroOut[50];
    char buffer[41];
    if (argc >= 2)
    {
        printf("Qual o numero do carro? %s\n", argv[1]);
        scanf("%i", &input);
        sprintf(carroIn, "CARRO%i.in", input);
        sprintf(carroOut, "CARRO%i.out", input);


        criarFifo(carroOut);
        criarFifo(carroIn);
        printf("Fim da criacao\n");

        printf("inicio excucao\n");
        
        printf("leitura\n");
        escrever(carroIn, "");
        ler(carroOut, buffer);
    }
    else
    {
        printf("Numero de argumentos invalido");
    }
    return 0;
}
*/
