#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem_Lectura[20], sem_Finalizar[20], sem_Leyendo;
sem_t sem_Escritura[20], sem_Finalizar[20], sem_Escribiendo;
sem_t sem_vacio;
sem_t sem_vacio, sem_ProtegeLectores, sem_ProtegeEscritores, sem_cola, sem_ProtegeCola;
int lectores = 0;
int escritores = 0;
int cola_escritores = 0;
int N2;


void *lector(void *threadArgs){

    while(1){
        int lector = *(int *)threadArgs;

        printf("[Lector %i] -> Esperando a intentar leer...\n", lector);
        sem_wait(&sem_Lectura[lector]);                     //Semáforo para esperar a que le manden leer.
        printf("[Lector %i] -> Intentando leer...\n", lector);

        if (lectores != 0 && lectores < N2) {
            sem_wait(&sem_Leyendo);                         //Semáforo para que haya N2 lectores simultáneos
            //if (escritores == 1) sem_wait(&sem_vacio); 
            sem_wait(&sem_ProtegeLectores);
            lectores ++;
            sem_post(&sem_ProtegeLectores);

            printf("[Lector %i] -> Leyendo...\n", lector);
            sem_wait(&sem_Finalizar[lector]);               //Semáforo para esperar a que le manden finalizar
            printf("[Lector %i] -> Fin lectura\n", lector);
            sem_wait(&sem_ProtegeLectores);
            lectores --;
            if (lectores == 0) sem_post(&sem_vacio);
            sem_post(&sem_ProtegeLectores);
            sem_post(&sem_Leyendo);
        }
        else{
            sem_wait(&sem_vacio);                                   //Si ya hay escritores esperamos
            if (cola_escritores == 1) sem_wait(&sem_cola);
            

            sem_wait(&sem_ProtegeLectores);                        //Semáforo para protejer a la vaiable
            lectores ++;
            sem_post(&sem_ProtegeLectores);

            sem_wait(&sem_Leyendo);                         //Semáforo para que haya N2 lectores simultáneos
            printf("[Lector %i] -> Leyendo...\n", lector);
            sem_wait(&sem_Finalizar[lector]);               //Semáforo para esperar a que le manden finalizar
            printf("[Lector %i] -> Fin lectura\n", lector);

            sem_wait(&sem_ProtegeLectores);                        //Semáforo para protejer a la vaiable
            lectores --;
            sem_post(&sem_ProtegeLectores);

            sem_post(&sem_vacio);
            sem_post(&sem_Leyendo);
            
        }
    }

}

void *escritor( void *threadArgs){
    while(1){
        int escritor = *(int *)threadArgs;

        printf("[Escritor %i] -> Esperando a intentar escribir...\n", escritor);
        sem_wait(&sem_Escritura[escritor]);  

        sem_wait(&sem_ProtegeCola);             //Semáforo para proteger
        cola_escritores=1;                      //Flag para la prioridad
        sem_post(&sem_ProtegeCola);

        printf("[Escritor %i] -> Intentando escibir...\n", escritor);

        if (lectores != 0 || escritores !=0) sem_wait(&sem_vacio);                               //Semáforo para esperar a que no haya nadie
        sem_wait(&sem_Escribiendo);                         //Semáforo para que sólo haya 1 Escritor.
        
        sem_wait(&sem_ProtegeEscritores);                   //Semáforo para protejer a la vaiable
        escritores ++;
        sem_post(&sem_ProtegeEscritores);

        printf("[Escritor %i] -> Escribiendo...\n", escritor);
        sem_wait(&sem_Finalizar[escritor]);                 //Semáforo para que le manden Finalizar.
        sem_post(&sem_cola);
        cola_escritores = 0;
        printf("[Escritor %i] -> Fin escritura\n", escritor);

        sem_wait(&sem_ProtegeEscritores);                    //Semáforo para protejer a la vaiable
        escritores --;
        sem_post(&sem_ProtegeEscritores);

        sem_post(&sem_Escribiendo);
        sem_post(&sem_vacio);
        
    }
}

int main(int argc, char* argv[]){

    

    if (argc != 4){
        printf("Uso: %s <Número máximo de lectores> <Número máximo de lectores concurrentes> <Número de escritores>\n", argv[0]);
        exit(-1);
    }

    int N1 = atoi(argv[1]);
    N2 = atoi(argv[2]);
    int N3 = atoi(argv[3]);
    pthread_t threadIdLectores[N1];
    pthread_t threadIdEscritores[N3];
    sem_init(&sem_Leyendo, 0, N2);
    sem_init(&sem_Escribiendo, 0, 1);
    sem_init(&sem_vacio, 0, 1);
    sem_init(&sem_ProtegeLectores, 0, 1);
    sem_init(&sem_ProtegeEscritores, 0, 1);
    sem_init(&sem_cola, 0, 0);
    sem_init(&sem_ProtegeCola, 0, 1);

    if (N2>=N1){
        printf("El número de lectores concurrentes debe ser menor que el de lectores totales\n");
        exit(-1);
    }

    for (int i = 0; i < N1; i++){
        int *arg = malloc(sizeof(int)); //para que no de warning
        *arg = i+1;
        pthread_create(&threadIdLectores[i], NULL, lector, arg);
        sem_init(&sem_Lectura[i], 0, 0);
        sem_init(&sem_Finalizar[i], 0, 0);
    }

    for (int i = 0; i<N3; i++){
        int *arg = malloc(sizeof(int)); //para que no de warning        
        *arg = i+1;
        pthread_create(&threadIdEscritores[i], NULL, escritor, arg);
        sem_init(&sem_Escritura[i], 0, 0);
        sem_init(&sem_Finalizar[i], 0, 0);
    }

    while(1){
        
        sleep(1);
        char opcion;
        int lector;
        int escritor;
        printf("1. Intentar Leer\n");
        printf("2. Finalizar Leer\n");
        printf("3. Intentar Escribir\n");
        printf("4. Finalizar Escribir\n");
        printf("5. Salir\n");
        scanf(" %c", &opcion);
        switch(opcion){
            case '1':
                printf("Introduzca el número del lector (de 1 a %i)\n", N1);
                scanf(" %i", &lector);
                sem_post(&sem_Lectura[lector]);
                break;  
            case '2':
                printf("Introduzca el número del lector (de 1 a %i)\n", N1);
                scanf(" %i", &lector);
                sem_post(&sem_Finalizar[lector]);
                break;
            case '3':
                printf("Introduzca el número del escritor (de 1 a %i)\n", N3);
                scanf(" %i", &escritor);
                sem_post(&sem_Escritura[escritor]);
                break;
            case '4':
                printf("Introduzca el número del escritor (de 1 a %i)\n", N3);
                scanf(" %i", &escritor);
                sem_post(&sem_Finalizar[escritor]);
                break;
            case '5':
                exit(1);
            default:
                printf("Opción no válida\n");
        }
    }
}