#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct arguments{
    int position;
    char *string;    
};


void *myThread( void *threadArg){
    struct arguments *args = (struct arguments *)threadArg;
    printf("Posición: %d, Parámetro: %s\n", args->position, args->string);
    pthread_exit(NULL); 
}

int main(int argc, char *argv[]){
    pthread_t threadId[argc];
    struct arguments array[argc];
    for (int i = 1; i< (argc); i++){
        array[i].position = i;
        array[i].string = argv[i];
        pthread_create(&threadId[i], NULL, myThread, (void *) &array[i]);
    }
    pthread_exit(NULL); 
    return 0;

}