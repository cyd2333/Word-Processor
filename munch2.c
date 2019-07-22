//
//  munch2.c
//  
//
//  Created by Arya Yu on 10/14/18.
//

#include "munch2.h"
#include "queue.h"
#define buffer 64

int toupper(int c);
void *to_upper (void *q){
    
    Q_combine* temp = ( Q_combine*)q;
    Queue *q_1 = temp->first;
    Queue *q_2 = temp->second;
    char *input = DequeueString(q_1);
    unsigned int i;
    int curNum;

    while(input) {
        for(i = 0; i < strlen(input); i++) {
            curNum = input[i];
	    if ((curNum > 96) &&(curNum < 123)) {
	        curNum = curNum -32;
	        input[i] = curNum;
	    }
         }
         EnqueueString(q_2, input);
         free(input);
         input = DequeueString(q_1);
    }
    EnqueueString(q_2, input);
    return 0;
}
