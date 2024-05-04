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
        printf("Pau-Torres ");
    }
    else{
        if ((p3 = fork()) == 0){
            printf("Carvajal ");
        }
        else{
            if ((p4 = fork()) == 0){
                printf("Jordi-Alba ");
                printf("Gavi ");
                printf("Nico-Williams ");
            }

            else{
                while(1){
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
            
}
