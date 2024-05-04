#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem_Escritura[20], sem_Finalizar[20], sem_Escribiendo;

void *escritor( void *threadArgs){
    while(1){
        int escritor = *(int *)threadArgs;
        printf("[Escritor %i] -> Esperando a intentar escribir...\n", escritor);
        sem_wait(&sem_Escritura[escritor]);
        printf("[Escritor %i] -> Intentando escibir...\n", escritor);
        sem_wait(&sem_Escribiendo);
        printf("[Escritor %i] -> Escribiendo...\n", escritor);
        sem_wait(&sem_Finalizar[escritor]);
        printf("[Escritor %i] -> Fin escritura\n", escritor);
        sem_post(&sem_Escribiendo);
    }
}

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Uso: %s <Número de escritores>\n", argv[0]);
        exit(-1);
    }

    int N3 = atoi(argv[1]);
    pthread_t threadId[N3];
    sem_init(&sem_Escribiendo, 0, 1);

    for (int i = 0; i<N3; i++){
        int *arg = malloc(sizeof(int)); //para que no de warning        
        *arg = i+1;
        pthread_create(&threadId[i], NULL, escritor, arg);
        sem_init(&sem_Escritura[i], 0, 0);
        sem_init(&sem_Finalizar[i], 0, 0);
    }

    while(1){
        char opcion;
        int escritor;
        printf("1. Intentar Escribir\n");
        printf("2. Finalizar Escribir\n");
        printf("3. Salir\n");
        scanf(" %c", &opcion);
        switch (opcion){
            case '1':
                printf("Introduzca el número del escritor (de 1 a %i)\n", N3);
                scanf(" %i", &escritor);
                sem_post(&sem_Escritura[escritor]);
                break;
            case '2':
                printf("Introduzca el número del escritor (de 1 a %i)\n", N3);
                scanf(" %i", &escritor);
                sem_post(&sem_Finalizar[escritor]);
                break;
            case '3':
                exit(1);
            default:
                printf("Opción no válida\n");
                break;
        }
    }
}