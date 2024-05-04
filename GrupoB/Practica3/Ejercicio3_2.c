#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(){
    key_t key;
    int sharedMemoryID;
    int *pointerAddress;
    char opcion;

    key = ftok("Ejercicio3_1.c", 3);
    if (key == -1) {
        perror("Error al generar la clave");
        exit(-1);
    }

    sharedMemoryID = shmget(key, sizeof(int), IPC_CREAT);
    if (sharedMemoryID == -1){
        perror("Error al crear memoria compartida");
        exit(-1);
    }

    pointerAddress = shmat(sharedMemoryID, NULL, 0);
    if(pointerAddress == (void *) -1) {
        perror("Error al asociar la zona de memoria compartida");
        exit(-1);
    }

    //printf("%d\n", *pointerAddress);
    do{
        printf("Pulse q para salir, cualquier otra para leer\n");
        scanf(" %c", &opcion);
        printf("El valor de la memoria compartida es: %d\n", *pointerAddress);
    }
    while (opcion != 'q');
    
    if (shmdt(pointerAddress) == -1){
        printf("No se ha podido desvincular el segmento");
    }
}