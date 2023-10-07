#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>

void criarFifo(char *str)
{
    if (mkfifo(str, 0666) == -1)
        printf("Erro na criação de pipe\n");
    else
        printf("FIFO %s criado com sucesso\n", str);
}

void main(int argc, char **argv)
{
    int input;
    char carroIn[50];
    char carroOut[50];
    char comando[300];
    if (argc >= 2)
    {
        int fd;

        printf("Qual o numero do carro?\n");
        scanf("%i", &input);
        sprintf(carroIn, "CARRO%i.in", input);
        sprintf(carroOut, "CARRO%i.out", input);

        criarFifo(carroIn);
        criarFifo(carroOut);
        fd = open(carroIn, O_RDONLY);

        size_t size;
        char buffer[20];
        
        while((size =read(fd, buffer, sizeof(buffer)))> 0)
        {
            write(STDIN_FILENO, buffer, size);
        }
        close(fd);
    }
    else
    {
        printf("Numero de argumentos invalido");
    }
    

}