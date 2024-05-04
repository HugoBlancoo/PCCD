#include <stdio.h>

int main(){
    char option;
    while(1){
        printf("Caminando por mi habitación...");
        scanf("%c", &option);
        if (option == '\n'){
            printf("Intentando entrar en mi sección crítica...\n");
            printf("Dentro de mi sección crítica.");
            scanf("%c", &option);
            if (option == '\n'){
                printf("He salido de mi sección crítica.\n\n");
            }
        }
    }
}