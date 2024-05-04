#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    key_t key;
    int memoryId;
    int *sharedMemory;
    int turno;
    char option;

    /*if (argc != 2){
        printf("Uso: %s <turno (0,1)>\n", argv[0]);
        exit(-1);
    }*/

    key = ftok("Ejercicio6.c", 3);

    if ((memoryId = shmget(key, sizeof(int), IPC_CREAT)) == -1){
        perror("shmget");
    }

    if ((sharedMemory = shmat(memoryId, NULL, 0)) == (void *)-1){
        perror("shmat");
    }

    *sharedMemory = -1; //valor que no se pueda dar aunque haya n procesos.

    while(1){
        printf("Caminando por la habitación...");
        scanf("%c", &option);
        if (option == '\n'){
            printf("Intentando acceder al pasillo de entrada de mi Sección Crítica...");
            scanf("%c", &option);
            if (option == '\n'){
                if (*sharedMemory == -1){
                    printf("Dentro del pasillo.");
                    scanf("%c", &option);
                    if (option == '\n'){
                        printf("He accionado el pulsador.\n");
                        *sharedMemory = 0;
                        printf("Dentro de mi Sección Crítica.");
                        scanf("%c", &option);
                        if (option == '\n'){
                            printf("He salido de mi sección crítica.");
                            scanf("%c", &option);
                            if (option == '\n'){
                                printf("He accionado el pulsador\n");
                                *sharedMemory = -1;
                            }
                        }
                    }
                }
                else{
                    printf("Puerta cerrada\n");
                }
            }
        }
    }
}