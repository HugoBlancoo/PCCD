#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]){
    if (argc != 3){
        printf("Uso: %s <numero_señal> <pid> \n", argv[0]);
        return 0;
    }
    kill(atoi(argv[2]), atoi(argv[1]));
}

