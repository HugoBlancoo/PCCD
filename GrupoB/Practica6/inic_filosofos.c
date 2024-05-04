#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg{
    long msgType;
    int tenedor;
};


int main(){
    int id;
    id = msgget(5, 0600 | IPC_CREAT);
    if (id  == -1){
        perror("msgget");
        exit(-1);
    }

    struct msg tenedor[6];
    for (int i=1; i<6; i++){
        tenedor[i].msgType = i;
        tenedor[i].tenedor = i;
        if(msgsnd(id, &tenedor[i], sizeof(struct msg), IPC_NOWAIT) == -1){
            perror("msgsnd");
            exit(-1);
        }
    }
}