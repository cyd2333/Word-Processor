#include "queue.h"
#include "munch1.h"
#include "munch2.h"
#include "reader.h"
#include "writer.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define q_size 10 

int main() {
    // create three queues
    Queue *q_1;
    Queue *q_2;
    Queue *q_3;
    
    q_1 = CreateStringQueue(q_size);
    q_2 = CreateStringQueue(q_size);
    q_3 = CreateStringQueue(q_size);
    // combine q_1 and q_2 with stucture com1
    Q_combine *com1;
    com1 = malloc(sizeof(Q_combine));
    // check the return value
    if (!com1) {
	fprintf(stderr,"Error: Cannot allocate memory\n");
	exit(EXIT_FAILURE);
    }
    com1->first = q_1;
    com1->second = q_2;
    
    // combine q_1 and q_2 with stucture com2
    Q_combine *com2;
    com2 = malloc(sizeof(Q_combine));
    if (!com1) {
        fprintf(stderr,"Error: Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }
    com2->first = q_2;
    com2->second = q_3;

    // create four threads 
    int err = 0;
    pthread_t thread_id[4]; 
    err += pthread_create(&thread_id[0], NULL, reader, (void*)q_1); 
    err += pthread_create(&thread_id[1], NULL, tostar, (void*)com1);
    err += pthread_create(&thread_id[2], NULL, to_upper, (void*)com2);
    err += pthread_create(&thread_id[3], NULL, writer, (void*)q_3);
    if(err != 0) {
        fprintf(stderr, "Cannot creating threads!!\n");
        exit(EXIT_FAILURE);
    }
    // wait until four threads terminated
    err += pthread_join(thread_id[0], NULL); 
    err += pthread_join(thread_id[1], NULL);
    err += pthread_join(thread_id[2], NULL);
    err += pthread_join(thread_id[3], NULL);
    if(err != 0) {
        fprintf(stderr, "error appearing when wait for threads\n");
        exit(EXIT_FAILURE);
    }

    // free the memory
    
    // print output
    fprintf(stderr,"Queue one: \n");
    PrintQueueStats(q_1);
    fprintf(stderr,"Queue two: \n");
    PrintQueueStats(q_2);
    fprintf(stderr,"Queue three: \n");
    PrintQueueStats(q_3);
    return 0;
}



