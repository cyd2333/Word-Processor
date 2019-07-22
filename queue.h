#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct Queue {
    int enqueueCount;
    int dequeueCount;
    int enqueueBlockCount;
    int dequeueBlockCount;
    char** elements;
    int front;
    int rear;
    int size;
    int capacity;
    int fullBlock;
    int emptyBlock;
    sem_t mutex;
    sem_t full;
    sem_t empty;
} Queue;

typedef struct Q_combine {
    Queue *first;
    Queue *second;
} Q_combine;

Queue *CreateStringQueue(int size);
void EnqueueString(Queue *q, char *string);
char * DequeueString(Queue *q);
void PrintQueueStats(Queue *q);

