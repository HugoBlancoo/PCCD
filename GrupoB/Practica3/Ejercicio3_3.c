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
    
    if (shmctl(sharedMemoryID, IPC_RMID, NULL) == -1){
        perror("Error al marcar el segmento para ser destruido");
    }
}