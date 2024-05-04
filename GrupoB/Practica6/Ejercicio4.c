#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg{
    long msgType;
    char msgText[100];
};

int main(){
    key_t key = 1;
    int msqid = 0;
    struct msg msg;

    if ((msqid =msgget(key, IPC_CREAT)) == -1){
        perror("msgget");
        exit(-1);
    }

    if (msgrcv(msqid, &msg, 100, 0, 0) == -1){
        perror("msgrcv");
        exit(-1);
    }

    printf("Mensaje recibido: %s\n", msg.msgText);

}