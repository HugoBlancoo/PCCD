#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_Hijos 3

int childFinished = 0;
int contadorHijos = 0;

void handler(int signal){
    if (signal == SIGCHLD){
        childFinished = 1;
    }
}

int main(){
    pid_t hijo1;
    pid_t hijo2;
    pid_t hijo3;
    int contadorHijos = 0;

    if ((hijo1 = fork())== 0){
        sleep(2);
        return 0;
    }
    else{
        if ((hijo2 = fork()) == 0){
            sleep(3);
            return 0;
        }
        else{
            if ((hijo3 = fork())== 0){
                sleep(4);
                return 0;
            }
        }
    }

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    sigaction(SIGCHLD, &sa, NULL);

    while(1){
        pause();
        if (childFinished == 1){
            contadorHijos ++;
            childFinished = 0;
            printf("Ha finalizado un proceso hijo\n");
            if (contadorHijos == NUM_Hijos){
                return 0;
            }

        }
    }
    return 0;
}