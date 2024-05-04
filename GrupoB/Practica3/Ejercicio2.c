#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

key_t key;
int sharedMemoryID;
int *pointerAddress;

int main(){
    key = 3000;    
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

    printf("%d\n", *pointerAddress);

    if (shmdt(pointerAddress) == -1){
        printf("No se ha podido denenlazar el segmento");
    }
}