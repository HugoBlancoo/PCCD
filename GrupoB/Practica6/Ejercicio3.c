#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main(int argc, char* argv[]){

    if (argc != 2){
        printf("Uso: %s <id>\n", argv[0]);
        exit(-1);
    }

    int msgid = atoi(argv[1]);

    key_t key = 1;
    int id = 0;

    if ((id = msgget(key, IPC_CREAT)) == -1){
        perror("msgget");
    }

    struct mymsg{
        long mtype;      // Tipo de mensaje
        char mtext[100]; // Texto del mensaje
    };

    struct mymsg msg;
    msg.mtype = 1;                     // Tipo de mensaje
    strcpy(msg.mtext, "Hola, mundo!"); // Texto del mensaje

    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1){
        perror("msgsnd");
        exit(1);
    }
}