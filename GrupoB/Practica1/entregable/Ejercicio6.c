#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char option;
    if (argc != 2){
        printf("Uso: %s <PID_Ascensor>\n", argv[0]);
        return 0;
    }
    printf("Elige una opción:\n -Subir(U)\n -Bajar(D)\n -Salir(E)\n");
    while(1){
        scanf(" %c", &option);
        //printf("%c", option);
        option = toupper(option);
        //printf("%c", option);
        switch (option)
        {
        case 'U':
            kill(atoi(argv[1]), SIGUSR1);
            break;
        case 'D':
            kill(atoi(argv[1]), SIGUSR2);
            break;
        case 'E':
            kill(atoi(argv[1]), SIGQUIT);
            return 0;
            break;
        default:
            printf("Elige una opción:\n -Subir(U)\n -Bajar(D)\n -Salir(E)\n");
            break;
        }
    
    }

}