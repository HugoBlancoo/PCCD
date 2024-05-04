#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

pid_t p2, p3, p4;
int status1, status2, status3, status4;

int main(){
    printf("Kepa ");
    fflush(stdout);
    if ((p2 = fork())== 0){
        execl("Ejercicio4/./p2", "Pau-Torres ", NULL);
        perror("Error al ejecutar execl()");
    }
    else{
        if ((p3 = fork()) == 0){
            execl("Ejercicio4/./p2","Carvajal ", NULL);
        }
        else{
            if ((p4 = fork()) == 0){
                execl("Ejercicio4/./p2","Jordi-Alba ", NULL);
                execl("Ejercicio4/./p2","Gavi ", NULL);
                execl("Ejercicio4/./p2","Nico-Williams ", NULL);
            }

            else{
                    printf("Ramos ");
                    wait(&status1);
                    wait(&status2);
                    wait(&status3);
                    printf("Rodri ");
                    printf("Isco ");
                    printf("Aspas");
                    wait(&status4);
                    printf("Morata\n");
                    return 0;
            } 
        }
    }
            
}
