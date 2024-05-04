#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

key_t key;
int sharedMemoryID;
int *pointerAddress;

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Uso: %s <numero>\n", argv[0]);
        exit(1);
    }

    key = 3000;     //Sirve para que todos los procesos que van a compartir memoria usen la misma clave.
                            //La clave con el mismo pathname y el mismo id es idéntica.

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

    *pointerAddress = atoi(argv[1]);

    if (shmdt(pointerAddress) == -1){
        printf("No se ha podido desvincular el segmento");
    }

    //printf("%d\n", *pointerAddress);
}