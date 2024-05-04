//Sin trampas, no acabado

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
    char *ingredientes[] = {"Papel", "Tabaco", "Fósforos"};
    int primerNumero,segundoNumero, id[4];
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
        primerNumero = rand() % 3;
        do {
        segundoNumero = rand() % 3;
        } while (segundoNumero == primerNumero);
        printf("[Proveedor]-> Poniendo ingredientes: %s, %s\n", ingredientes[primerNumero], ingredientes[segundoNumero]);

        msg.msgType=primerNumero;
        msg.mensaje=primerNumero;
        msgsnd(id[primerNumero], &msg, sizeof(struct msg), 0);

        msg.msgType=segundoNumero;
        msg.mensaje=segundoNumero;
        msgsnd(id[segundoNumero], &msg, sizeof(struct msg), 0);


        printf("Esperando a que acabe de fumar\n");
        msgrcv(id[3], &msg, sizeof(struct msg),1, 0);
    }
}