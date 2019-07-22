#include "writer.h"
#include "queue.h"

void *writer (void *q) {
        Queue *q_1 = (Queue*)q;
	int count=0;
	char *outputString = DequeueString(q_1);
       
	while(outputString){
	count++;
        printf("%s",outputString);
//	fflush(stdout);
	free(outputString);
        outputString = DequeueString(q_1);	
	}

	 printf("Total number of lines: %d \n", count);
         return 0;   	     
}
