#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

key_t key;
int sharedMemoryID;
int *pointerAddress;
int num = 0;

int main(){
    char opcion;
    key = ftok("Ejercicio3_1.c", 3);
    
    if( (sharedMemoryID = shmget(key, sizeof(int), IPC_CREAT)) == -1 ){
        perror("Error al crear la memoria compartida");
        exit(-1);
    }

    if ( (pointerAddress = shmat(sharedMemoryID, NULL, 0)) == (void *) -1 ){
        perror("Error al asociar la zona de memoria compartida");
        exit(-1);
    }
    
   
    do{
        printf("Intoduzca un número o pulse q para salir\n");
        scanf(" %s", &opcion);
        if (opcion != 'q'){
            num = atoi(&opcion);
            *pointerAddress = num;
        }
        while (getchar() != '\n');
        //printf("%d\n", *pointerAddress);
    }
    while (opcion != 'q');

    if (shmdt(pointerAddress) == -1){
        printf("No se ha podido desvincular el segmento");
    }
}