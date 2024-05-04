#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg{
    long msgType;
    int tenedor;
};

int main(int argc, char* argv[]){
    int id;

    if (argc != 2){
        printf("Uso: %s <numero de filósifo(1-5)>\n",argv[0]);
        exit(-1);
    }

    id = msgget(5, 0600 | IPC_CREAT);
    if (id == -1){
        perror("msgget");
    }

    struct msg tenedor[6];

    int i = atoi(argv[1])-1;
    if (i == 0){
        i = 5;
    }

    printf("Filósofo %d intentando coger el tenedor %d...\n", atoi(argv[1]), i);
    msgrcv(id, &tenedor[atoi(argv[1])], sizeof(struct msg), i, 0);
    printf("El filósofo %d cogió el tenedor %d\n", atoi(argv[1]), i);

    printf("Filósofo %d intentando coger el tenedor %d...\n", atoi(argv[1]), atoi(argv[1]));
    msgrcv(id, &tenedor[atoi(argv[1])], sizeof(struct msg), atoi(argv[1]), 0);
    printf("El filósofo %d cogió el tenedor %d\n", atoi(argv[1]), atoi(argv[1]));


    printf("*********** Filósofo %d comiendo ***********\n", atoi(argv[1]));
    sleep(5);

    printf("Filósofo %d devolviendo los tenedores...\n", atoi(argv[1]));

    tenedor[atoi(argv[1])].msgType =atoi(argv[1]);
    tenedor[atoi(argv[1])].tenedor =atoi(argv[1]);
    tenedor[i].msgType = i;
    tenedor[i].tenedor = i;

    msgsnd(id, &tenedor[atoi(argv[1])], sizeof(struct msg), IPC_NOWAIT);
    msgsnd(id, &tenedor[i], sizeof(struct msg), IPC_NOWAIT);

}