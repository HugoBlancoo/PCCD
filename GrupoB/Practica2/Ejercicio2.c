#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define NUM_Hijos 3

int main(){
    pid_t hijo1, hijo2, hijo3;
    int contadorHijos = 0;
    int status1, status2, status3;

    if ((hijo1 = fork())== 0){  //Esta es la parte del hijo
        sleep(2);
        exit(0);                //El código de salida se guarda en WEXITSTATUS
    }
    else{
        if ((hijo2 = fork()) == 0){
            sleep(3);
            exit(1);
        }
        else{
            if ((hijo3 = fork())== 0){
                sleep(4);
                exit(-1);
            }
            else{               //Esta es la parte del código
                while(1){
                    wait(&status1);
                    contadorHijos++;
                    printf("El proceso hijo 1, con pid %d ha terminado con código de salida %d\n", hijo1, WEXITSTATUS(status1));
                    wait(&status2);
                    contadorHijos++;
                    printf("El proceso hijo 2, con pid %d ha terminado con código de salida %d\n", hijo2, WEXITSTATUS(status2));
                    wait(&status3);
                    contadorHijos++;
                    printf("El proceso hijo 3, con pid %d ha terminado con código de salida %d\n", hijo3, WEXITSTATUS(status3));

                    if (contadorHijos == NUM_Hijos){
                            return 0;
                    }
                }
            }
        }
    }
}