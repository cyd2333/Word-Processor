//  reader.c
//  
//
//  Created by Arya Yu on 10/13/18.
//

#include "reader.h"
#include "queue.h"
#include "string.h"

//#include thread_data
#define BUFFER_SIZE 1024


void *reader  (void *q)
{   
    Queue *q_1 = (Queue*)q;	
    char *input;

    int count=0;
    input= calloc(BUFFER_SIZE, sizeof(char));
    // check return value
    if(!input) {
        fprintf(stderr,"Error: cannot get allocated memory\n");
	exit(EXIT_FAILURE);
    }
    while(1) {  
        char next = fgetc(stdin);
	// check return value
	if(!next) 
	    fprintf(stderr, "Error in reading file\n");
	// if it is the end of file, return it
	if(next == EOF) {
	    if(count != 0) {
                EnqueueString(q_1, input);
                free(input);
                input= calloc(BUFFER_SIZE, sizeof(char));
		break;
	    }
	    break;
	}
	input[count] = next;
	count ++;
	// if it is next line, move to next line 
	// and enqueue the string
	if(next == '\n') {
	   EnqueueString(q_1, input);
           free(input);
	   input= calloc(BUFFER_SIZE, sizeof(char));	   
	   count = 0;
	}
	// if the string is longer than buffer_size,
	// ingore the whole line
	if(count == BUFFER_SIZE) {
	    fprintf(stderr,"Error input: input string too long\n");
	    count = 0;
            free(input);
            input= calloc(BUFFER_SIZE, sizeof(char));
	    // read untill next line
	    while(1) {
                if(feof(stdin) || next == '\n')
		    break;
		else 
		    next = fgetc(stdin);
	    }
 	}
    }
    // deliver null as temination
    EnqueueString(q_1, NULL);
    free(input);
    return 0;
}

