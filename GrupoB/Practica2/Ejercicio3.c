#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    pid_t hijo1;
    pid_t hijo2;
    pid_t hijo3;
    int status1, status2, status3;

    if ((hijo1 = fork()) == 0){
        //Esta es la parte del hijo;
        sleep(10);
        exit(0);
    }
    else{
        if ((hijo2 = fork()) == 0){
            sleep(3);
            exit(1);
        }
        else{
            if ((hijo3 = fork()) == 0){
                sleep(4);
                exit(-1);
            }
            else{
                //Esta es la parte del padre
                int pid1 = waitpid(hijo1, &status1, 0);
                //wait(&status1);
                printf("El proceso hijo 1, con pid %d ha finalizado con código de salida %d\n", pid1, WEXITSTATUS(status1));

                int pid2 = waitpid(hijo2, &status2, 0);
                //wait(&status2);
                printf("El proceso hijo 2, con pid %d ha finalizado con código de salida %d\n", pid2, WEXITSTATUS(status2));

                int pid3 = waitpid(hijo3, &status3, 0);
                //wait(&status3);
                printf("El proceso hijo 3, con pid %d ha finalizado con código de salida %d\n", pid3, WEXITSTATUS(status3));
            }
        }
    }      
    return 0;
}