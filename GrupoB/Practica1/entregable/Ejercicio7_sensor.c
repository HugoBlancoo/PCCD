#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>

const int T_PISO = 2;
int pidAscensor;
int piso;

void manejador(int signal){
    if (signal == SIGHUP){
        sleep(T_PISO);
        kill(pidAscensor, SIGILL);
    }
}

int main(){
    printf("PID: %d\n", getpid());
    printf("Introduzca el piso al que pertenece:");
    scanf("%d", &piso);
    printf("Introduzca el PID del ascensor:\n");
    scanf(" %d", &pidAscensor);
    

    struct sigaction sa;
    sa.sa_handler = manejador;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    sigaction(SIGHUP, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);

    while(1){
        pause();
    }
}