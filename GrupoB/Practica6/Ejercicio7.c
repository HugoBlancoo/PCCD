#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg{
    long msgType;
    int mensaje ;
}; 

int main(int argc, char* argv[]){

    char *ingredientesNecesarios[] = {"Papel y Fósforos", "Papel y Tabaco", "Tabaco y Fósforos"};

    int id[4];
    struct msg msg;
    msg.msgType=1;
    msg.mensaje=1;

    if (argc != 2){
        printf("Uso: %s <número fumador>\n", argv[0]);
        exit(-1);
    }

    int fumador = atoi(argv[1]);

    for (int i =0; i<4; i++){
        id[i] = msgget(7+i, 0666|IPC_CREAT);    //+i para crear claves distintas.
        if (id[i] == -1){
            perror("msgget");
            exit(-1);
        }
    }

    while(1){
        printf("[Fumador %i]-> Intentando coger %s\n", fumador, ingredientesNecesarios[fumador-1]);
        msgrcv(id[fumador-1], &msg, sizeof(struct msg), 1, 0);  
        printf("[Fumador %i]-> Fumando...\n", fumador);
        sleep(5);
        printf("[Fumador %i]->He terminado de fumar\n", fumador);
        msgsnd(id[3], &msg, sizeof(struct msg), 0);
        
    }
}