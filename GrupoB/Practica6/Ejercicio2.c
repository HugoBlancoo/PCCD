#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char* argv[]){

    if (argc != 2){
        printf("Uso: %s <id>\n", argv[0]);
        exit(-1);
    }

    int id = atoi(argv[1]);

    if( msgctl(id, IPC_RMID, NULL) == -1){
        perror("msgctl");
    }

    }