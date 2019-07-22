//
//  munch1.c
//  
//
//  Created by Arya Yu on 10/14/18.
//

#include "munch1.h"
#include "queue.h"
#define buffer 64


void* tostar(void *q){
    Q_combine* temp = (Q_combine*)q;
    Queue *q_1 = temp->first;
    Queue *q_2 = temp->second;
    char *input = DequeueString(q_1);
    unsigned int i = 0;
    while (input) {
	for(i=0;i < strlen(input);i++) {
            if(input[i] == ' ') 
                input[i] = '*';
	    
	}
        EnqueueString(q_2, input);
	free(input);
        input = DequeueString(q_1);
    }
    EnqueueString(q_2, input);
    return 0;
}
