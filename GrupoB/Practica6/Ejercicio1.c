#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    key_t key = 1;
    int id = 0;

    if ((id =msgget(key, IPC_CREAT)) == -1){
        perror("msgget");
        exit(-1);
    }
    printf("%i\n", id);
}