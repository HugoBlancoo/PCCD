//Aún no conseguí que funcione

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int piso = 0;
int pisoMax = 0;
int contadorSubida = 0;
int contadorBajada = 0;
const int T_PISO = 2;
int busy = 0;
int pidSensor;
int pidSensor1;
int pidSensor2;

void manejador(int signal){
    if (busy == 0){
        //printf("El proceso ha recibido la señal %d\n", signal);
        if (signal == SIGUSR1){
            if (piso == pisoMax){
                printf("No se puede subir más\n");           
            }
            if (piso == 0){
                kill(pidSensor, SIGHUP);
                busy = 1;
                piso ++;
                contadorSubida ++;
                printf("Subiendo...\n");
            }
            if (piso == 1){
                kill(pidSensor1, SIGHUP);
                busy = 1;
                piso ++;
                contadorSubida ++;
                printf("Subiendo...\n");
            }
            if (piso == 2){
                kill(pidSensor2, SIGHUP);
                busy = 1;
                piso ++;
                contadorSubida ++;
                printf("Subiendo...\n");
            }
            else {
                kill(pidSensor, SIGHUP);
                busy = 1;
                piso ++;
                contadorSubida ++;
                printf("Subiendo...\n");
                /*sleep(T_PISO);
                printf("Piso %d\n", piso);
                busy = 0;*/
            }
        }

        if (signal == SIGUSR2){
            if (piso == 0){
                printf("No se puede bajar más\n");
            }
            else{
                kill(pidSensor, SIGINT);
                busy = 1;
                piso --;
                contadorBajada ++;
                printf("Bajando...\n");
                sleep(T_PISO);
                printf("Piso %d\n", piso);
                busy = 0;
            }
        }

        if (signal == SIGQUIT){
            printf("El ascensor ha subido %d veces y ha bajado %d veces\n", contadorSubida, contadorBajada);
            exit(-1);
        }
    }
    else{
        if (signal == SIGILL){
                printf("Piso %d\n", piso);
                busy = 0;
        }
        else{
            printf("Está ocupado\n");
        }
    }    
}

int main (int argc, char *argv[]){
    if (argc != 2){
        printf("Uso: %s <pisoMax>\n", argv[0]);
        return 0;
    }
    pisoMax = atoi(argv[1]);
    //printf("Piso max: %d\n", pisoMax);
    printf("PID: %d\n", getpid());
    printf("Intoduzca el PID de cada sensor:\n");
    scanf(" %d %d", &pidSensor1, &pidSensor2);

    struct sigaction sa;
    sa.sa_handler = manejador;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    while (1){
        pause();
    }
    return 0;
}