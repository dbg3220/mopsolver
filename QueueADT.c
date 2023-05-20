//
// File: QueueADT.c
// Description: A library module that implements a queue abstract data type
//  for portable use in client programs.
//
// @author Damon Gonzalez
//
// @username dbg3220
//
// @date 3/14/2022
//

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// A struct to represent a node in the queue
typedef struct node {
    void * data;
    struct node * tail;
} node;

// A struct to represent the whole queue. Contains a pointer to the front and
// back of the queue so that enqueue and dequeue operations both take constant
// time.
typedef struct QueueStruct {
    node * head;
    node * back;
    int size;
} * QueueADT;

#define _QUEUE_IMPL_
#include "QueueADT.h"

QueueADT que_create(){
    QueueADT queue = (QueueADT)malloc( sizeof( struct QueueStruct ) );
    queue->head = NULL;
    queue->back = NULL;
    queue->size = 0;
    return queue;
}

void que_destroy( QueueADT queue ){
    que_clear( queue );
    free( queue );
}

void que_clear( QueueADT queue ){
    node * walk = queue->head;
    while( walk != NULL ){
        node * temp = walk->tail;
        free( walk );
        walk = temp;
    }
    queue->head = NULL;
    queue->back = NULL;
    queue->size = 0;
}