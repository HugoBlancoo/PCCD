#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char keyboardValue;
int caracterCounter = 0;

void *myThread(void *vargp){
    printf("Introduzca un caracter (para salir utilize q)\n");

    while(keyboardValue != 'q'){
        keyboardValue = getchar();
        getchar(); //para ignorar el \n que introducimos al darle al enter
        caracterCounter++;
    }
    return NULL;
}

int main(){
    pthread_t threadId;

    if (pthread_create(&threadId, NULL, myThread, NULL) == -1){
        perror("Error al crear el thread");
        exit(-1);
    }
    else{
        while(keyboardValue != 'q'){
            sleep(1);
            printf("Número de caracteres recibidos: %d \n", caracterCounter);
        }
    }
    return 0;
}