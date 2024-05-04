#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>

struct msg{
    long msgType;
    int mensaje ;
}; 


int main(){
    char *ingredientes[] = {"Papel y Fósforos", "Papel y Tabaco", "Tabaco y Fósforos"};
    int numero, id[4];
    struct msg msg;
    msg.msgType=1;
    msg.mensaje=1;

    // Inicializar la semilla de la función rand() con el tiempo actual
    srand(time(NULL));

    for (int i =0; i<4; i++){
        id[i] = msgget(7+i, 0666|IPC_CREAT);
        msgctl(id[i], IPC_RMID, NULL);  //Por si había algo en la cola.
        id[i] = msgget(7+i, 0666|IPC_CREAT);
        if (id[i] == -1){
            perror("msgget");
            exit(-1);
        }
    }
    
    while(1){
        // Generar un número aleatorio entre 0 y 2
        numero = rand() % 3;
        printf("[Proveedor]-> Poniendo ingredientes: %s\n", ingredientes[numero]);
        msgsnd(id[numero], &msg, sizeof(struct msg), 0);
        printf("Esperando a que acabe de fumar\n");
        msgrcv(id[3], &msg, sizeof(struct msg),1, 0);
    }
}