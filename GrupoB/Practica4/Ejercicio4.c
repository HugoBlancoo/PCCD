#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem_Lectura[20], sem_Finalizar[20], sem_Leyendo;

void *lector(void *threadArgs){

    while(1){
        int lector = *(int *)threadArgs;

        printf("[Lector %i] -> Esperando a intentar leer...\n", lector);
        sem_wait(&sem_Lectura[lector]);
        printf("[Lector %i] -> Intentando leer...\n", lector);
        sem_wait(&sem_Leyendo);
        printf("[Lector %i] -> Leyendo...\n", lector);
        sem_wait(&sem_Finalizar[lector]);
        printf("[Lector %i] -> Fin lectura\n", lector);
        sem_post(&sem_Leyendo);
    }

}


int main(int argc, char* argv[]){

    char opcion;

    if (argc != 3){
        printf("Uso: %s <Número máximo de lectores> <Número máximo de lectores concurrentes>\n", argv[0]);
        exit(-1);
    }

    int N1 = atoi(argv[1]);
    int N2 = atoi(argv[2]);
    pthread_t threadId[N1];
    sem_init(&sem_Leyendo, 0, N2);

    if (N2>=N1){
        printf("El número de lectores concurrentes debe ser menor que el de lectores totales\n");
        exit(-1);
    }

    for (int i = 0; i < N1; i++){
        int *arg = malloc(sizeof(int)); //para que no de warning
        *arg = i+1;
        pthread_create(&threadId[i], NULL, lector, arg);
        sem_init(&sem_Lectura[i], 0, 0);
        sem_init(&sem_Finalizar[i], 0, 0);
    }

    while(1){
        sleep(.5);
        int lector;
        printf("1. Intentar Leer\n");
        printf("2. Finalizar Leer\n");
        printf("3. Salir\n");
        scanf(" %c", &opcion);
        switch(opcion){
            case '1':
                printf("Introduzca el número del lector (de 1 a %i)\n", N1);
                scanf(" %i", &lector);
                sem_post(&sem_Lectura[lector]);
                break;  
            case '2':
                printf("Introduzca el número del lector (de 1 a %i)\n", N1);
                scanf(" %i", &lector);
                sem_post(&sem_Finalizar[lector]);
                break;
            case '3':
                exit(1);
            default:
                printf("Opción no válida\n");
        }
    }
}