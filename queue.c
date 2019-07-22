#include "queue.h"

Queue *CreateStringQueue(int size) {
    // create a queue
    Queue *q;
    // initialize the queue with input size
    q = (Queue*)malloc(sizeof(Queue));
    if(!q) {
        fprintf(stderr,"Error: cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    q->elements = malloc(sizeof(char*)*size);
    if(!q->elements) {
        fprintf(stderr,"Error: cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    // initialize the original string into null
    for (int i = 0; i < size; i++) 
        (q->elements)[i] = NULL;
    q->enqueueCount = 0;
    q->dequeueCount = 0;
    q->enqueueBlockCount = 0;
    q->dequeueBlockCount = 0;
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = size;
    sem_init(&q->mutex,0,1);
    sem_init(&q->full,0,0);
    sem_init(&q->empty,0,0);
    q->fullBlock = 0;
    q->emptyBlock = 0;
    return q;
}

void EnqueueString(Queue *q, char *string) {
    
    // lock the queue before operaring
    sem_wait(&q->mutex);
    int cap = q->capacity;
    int *f = &(q->front);
    //check whether the queue is full
    if ((q->size) == cap) {
        q->enqueueBlockCount ++;
	q->fullBlock ++;
	sem_post(&q->mutex);
	sem_wait(&q->full);
	sem_wait(&q->mutex);
    }
    // insert string into queue
    if(string) {
        int length = strlen(string)+1;
        q-> elements[q->front] = malloc(sizeof(char)*length);
	if(!q-> elements[q->front]) {
	    fprintf(stderr,"Error: cannot allocate memory\n");
	    exit(EXIT_FAILURE);
	}
        memcpy(q->elements[q->front], string, length);
    } else {
        q-> elements[q->front] = string;

    }
    // size, front and enqueueCount increament
    (q->size) ++;
    *f += 1;
    (q->enqueueCount) ++;
    if(*f > (cap - 1)) 
        *f = *f - cap;
    // allow dequeue if necessary;
    if (q->emptyBlock > 0) {
        sem_post(&q->empty);
	q->emptyBlock --;
    }
    // unlock the queue
    sem_post(&q->mutex);
}

char * DequeueString(Queue *q) {
    // lock the queue before operating
    sem_wait(&q->mutex);
    int *r = &(q->rear);
    int *size = &(q->size);
    int cap = q->capacity;
    // check whether it is empty
    if (*size == 0) {
        q->dequeueBlockCount ++;
	q->emptyBlock ++;
	sem_post(&q->mutex);
	sem_wait(&q->empty);
	sem_wait(&q->mutex);
    }
    // generate output string;
    char *output = q->elements[*r];
    // size, rear and dequeueCount increament or decrement
    (*size) --;
    q->dequeueCount ++;
    (*r) ++;
    if (*r > (cap-1)) 
        *r = *r - cap;
    // allow enqueue if necessary
    if (q->fullBlock > 0) {
        sem_post(&q->full);
	q->fullBlock --;
    }
    // unlock the queue
    sem_post(&q->mutex);
    // return output
    return output;
}


void PrintQueueStats(Queue *q) {
    fprintf(stderr,"%d\n", q->enqueueCount);
    fprintf(stderr,"%d\n", q->dequeueCount);
    fprintf(stderr,"%d\n", q->enqueueBlockCount);
    fprintf(stderr,"%d\n", q->dequeueBlockCount);

}
