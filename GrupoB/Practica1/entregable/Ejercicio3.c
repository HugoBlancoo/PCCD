#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

__uint64_t vectorBits = 0;

void manejador(int signal){
    if(signal > 0 && signal <= 64)
      vectorBits  |= (1ULL << (signal - 1)); //1ULL representa el valor de 1 como un numero entero de por lo menos 64 bits
    printf("Proceso p3 ha recibido la señal %d\n", signal);
    if (signal == 15){
        for (int i =63; i>0; i--){
            unsigned char bit = (vectorBits >> i) & 1;
            printf("%u", bit);
        }printf("\n");
        exit(-1);
    }
}
 
int main(){
    printf("PID: %d\n", getpid());

    struct sigaction sa;

    sa.sa_handler = manejador;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    for (int i = 1; i < 64; i++) {
        sigaction(i, &sa, NULL);
    }
    while(1){
        pause();
    }
    return 0;
}