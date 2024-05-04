#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    key_t key;
    int id;
    int *memory;
    int turno;
    char option;

    if(argc != 2){
        printf("Uso: %s <turno (0-1)>\n", argv[0]);
        exit(-1);
    }
    turno = atoi(argv[1]);
    key = ftok("Ejercicio5.c", 3);

    if ((id = shmget(key, sizeof(int), IPC_CREAT)) == -1){
        perror("shmget");
    }

    if ((memory = shmat(id, NULL, 0)) == (void *)-1){
        perror("shmat");
    }

    *memory = 0;

    while(1){
        printf("Caminando por mi habitación...");
        scanf("%c", &option);
        if (option == '\n'){
            printf("Intentando entrar en mi sección crítica...\n");
            if(turno == *memory){
                printf("Dentro de mi sección crítica.");
                scanf("%c", &option);
                if (option == '\n'){
                    printf("He salido de mi sección crítica.\n ");
                    if (*memory == 0 ) *memory = 1;
                    else *memory = 0;
                    printf("He accionado el pulsador.\n");
                }
            }
            else{
                printf("Puerta cerrada\n");
            }
        }
    }
}