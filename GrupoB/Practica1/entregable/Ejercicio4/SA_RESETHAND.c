#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int contadorSIGUSR1 = 0;
int contadorSIGUSR2 = 0;

void manejador(int signal){
    printf("El proceso ha recibido la señal %d\n", signal);
    
    if (signal == SIGUSR1){
        contadorSIGUSR1++;  //La señal SIGUSR1
    }

    if (signal == SIGUSR2){
        contadorSIGUSR2++;  //La señal SIGUSR2
    }
    if (signal == SIGTERM){
        printf("Número de señales SIGUSR1 = %d\n", contadorSIGUSR1);
        printf("Número de señales SIGUSR2 = %d\n", contadorSIGUSR2);
        exit(-1);           //si la señal es SIGTERM finaliza el proceso e imprime los contadores
    }
}

int main(){
    printf("PID: %d\n", getpid());

    struct sigaction sa;
    sa.sa_handler = manejador;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESETHAND;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    while(1){
        pause();
    }

    return 0;
}
