#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <sys/msg.h> // Msgget
#include <sys/ipc.h> // Msgget
#include <pthread.h> // Hilos
#include <semaphore.h> // Semaforos

// Constantes y estructuras
#define nUsuarios 3

typedef struct {
    int mtype;
    int idOrigen;
    float ticket;
} msg;

// Variables globales
key_t clave;
sem_t entradaSeccionCritica;
float ticket, minTicket = 0;
int quieroEntrar = 0, miID, colaNodos[nUsuarios - 1], pendientes = 0;

// Prototipos de funciones
float findGreater(float, float);
void* receive();
void* inicilizarBuzonSemaforo();

// Función principal
int main(int argc, char* argv[]) {
    msg mensajeOut;
    pthread_t idHilo;
    int error, idNodos[nUsuarios - 1];

    // Inicialización
    clave = atoi(argv[1]);
    inicilizarBuzonSemaforo();

    // Recoger IDs de buzones de otros procesos
    for (int i = 0; i < (nUsuarios - 1); i++) {
        printf("Introduzca el ID del buzon del usuario %i: ", i);
        scanf("%i", &idNodos[i]);
    }

    // Crear hilo de recepción
    error = pthread_create(&idHilo, NULL, receive, NULL);
    if (error == -1) {
        printf("Error durante la creación del hilo del método de recepción. Cerrando programa.\n");
        exit(-1);
    }
    printf("Hilo creado correctamente.\n\n");

    // Bucle principal
    while (1) {
        sleep(1);
        fflush(stdin);
        printf("Esperando activación.\n");
        while (getchar() != 'n');
        srand((unsigned)time(NULL));

        // Generar número aleatorio para ticket
        ticket = minTicket + (float)((rand() % 1000) / 1000.0f);
        quieroEntrar = 1;

        // Definir mensaje para otros nodos
        mensajeOut.mtype = 1;
        mensajeOut.ticket = ticket;
        mensajeOut.idOrigen = miID;

        // Realizar peticiones para entrar a la sección crítica
        for (int i = 0; i < (nUsuarios - 1); i++) {
            do {
                error = msgsnd(idNodos[i], &mensajeOut, sizeof(mensajeOut), 0);
                if (error == -1) {
                    printf("Error durante el envío de peticiones. Reintentado.\n\n");
                }
            } while (error != 0);
        }
        printf("Peticiones enviadas correctamente.\n");

        // Esperar al semáforo de paso
        sem_wait(&entradaSeccionCritica);
        printf("Se ha recibido respuesta a todas las peticiones.\n\n");
        printf("El nodo ha entrado en la sección crítica.\n");

        // Salir de la sección crítica
        while (getchar() != 's');
        printf("El nodo ha salido de la sección crítica.\n\n");

        // Responder a peticiones pendientes
        mensajeOut.mtype = 2;
        mensajeOut.idOrigen = miID;
        quieroEntrar = 0;
        printf("Enviando confirmaciones pendientes.\n");
        for (int i = 0; i < pendientes; i++) {
            do {
                error = msgsnd(idNodos[i], &mensajeOut, sizeof(mensajeOut), 0);
                if (error == -1) {
                    printf("Error durante el envío de peticiones. Reintentado.\n\n");
                }
            } while (error != 0);
            printf("Confirmación enviada.\n");
        }
        pendientes = 0;
    }

    return 0;
}

// Función para encontrar el mayor de dos números
float findGreater(float n1, float n2) {
    return (n1 > n2) ? n1 : n2;
}

// Función para inicializar el buzón y el semáforo
void* inicilizarBuzonSemaforo() {
    int error;

    // Inicializar el buzón
    miID = msgget(clave, IPC_CREAT | 0777);
    if (miID == -1) {
        printf("\nError creando el buzón. Cerrando programa.\n");
        exit(-1);
    }
    printf("Buzón con ID %i, creado correctamente.\n", miID);

    // Inicializar el semáforo de paso
    error = sem_init(&entradaSeccionCritica, 0, 0);
    if (error == -1) {
        printf("\nError inicializando el semáforo de paso. Cerrando programa.\n");
        exit(-1);
    }

    return 0;
}

// Función para recibir mensajes
void* receive() {
    int error, nConfirmaciones = 0;
    msg mensajeIn, mensajeOut;

    while (1) {
        error = msgrcv(miID, &mensajeIn, sizeof(mensajeIn), 0, 0);
        if (error == -1) {
            printf("Error durante el recibimiento de peticiones. Reintentado.\n\n");
        } else if (mensajeIn.mtype == 2) {
            printf("Confirmación recibida.\n");
            nConfirmaciones++;
            if (nConfirmaciones == (nUsuarios - 1)) {
                sem_post(&entradaSeccionCritica);
                nConfirmaciones = 0;
            }
        } else if (quieroEntrar == 1) {
            colaNodos[pendientes] = mensajeIn.idOrigen;
            pendientes++;
        } else if ((quieroEntrar == 0) || (ticket > mensajeIn.ticket) || (ticket == mensajeIn.ticket && miID > mensajeIn.idOrigen)) {
            minTicket = findGreater(minTicket, mensajeIn.ticket);
            mensajeOut.idOrigen = miID;
            mensajeOut.ticket = 0;
            mensajeOut.mtype = 2;

            do {
                error = msgsnd(mensajeIn.idOrigen, &mensajeOut, sizeof(mensajeOut), 0);
                if (error == -1) {
                    printf("Error durante el recibimiento de peticiones. Reintentado.\n\n");
                }
                printf("Confirmación enviada.\n");
            } while (error != 0);
        }
    }
}
