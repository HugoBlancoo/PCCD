#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int turno;
    key_t key1, key2;
    int id1, id2;
    int *openDoor, *busy;
    int secondDoor[2];
    char option;
    int contrario;

    if (argc != 2){
        printf("Uso: %s <turno(1-0)>", argv[0]);
        exit(-1);
    }

    turno = atoi(argv[1]);
    key1 = ftok(".", 1);
    key2 = ftok(".", 0);
    if (key2 == -1){
        perror("key");
    }
    
    if (((id1 = shmget(key1, sizeof(int), IPC_CREAT)) == -1) || ((id2 = shmget(key2, sizeof(int), IPC_CREAT)) == -1)) {
        perror("Shmget");
    }


    if (((openDoor = shmat(id1, NULL, 0)) == (void *)-1) || ((busy = shmat(id2, NULL, 0)) == (void *)-1)){
        perror("Shmat");
    }

    openDoor[0] = 1;
    openDoor[1] = 1;
    *busy = 0;
    if (turno == 0){
        contrario = 1;
    }else{
        contrario = 0;
    }

    while(1){
        printf("Caminando por mi habitación...");
        scanf("%c", &option);
        if (option == '\n'){
            printf("Dentro del pasillo.");
            scanf("%c", &option);
            if (option == '\n'){
                printf("He accionado el pulsador");
                if (*busy == 0){
                    openDoor[turno] = 1;
                    openDoor[contrario] = 0;
                }
                scanf("%c", &option);
                if (option == '\n'){
                    printf("Intentando acceder a la sección crítica...\n");
                    if (openDoor[turno] == 1 && *busy == 0){
                        printf("Dentro de mi sección crítica");
                        *busy = 1;
                        secondDoor[turno] = 0;
                        secondDoor[contrario] = 1;
                        scanf("%c", &option);
                        if (option == '\n'){
                            printf("He salido de mi sección crítica");
                            scanf("%c", &option);
                            if (option == '\n'){
                                printf("He accionado el pulsador\n");
                                *busy = 0;
                                openDoor[turno] = 0;
                            }
                        }
                    }
                    else{
                        printf("Puerta cerrada, saliendo del pasillo");
                        scanf("%c", &option);
                        if (option == '\n'){
                            printf("He accionado el pulsador\n");
                            secondDoor[turno] = 1;
                        }
                    }
                }
            }
        }
    }
}