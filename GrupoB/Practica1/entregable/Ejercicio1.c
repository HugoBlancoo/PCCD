#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void manejador(int signal){
    printf("Proceso p1 ha recibido la señal %d\n", signal);
}

int main(){
    for (int i = 1; i<64; i++){
        signal(i, manejador);
    }
    printf("PID: %d\n", getpid());

   while(1){
        pause();
    }

    return 0;
}