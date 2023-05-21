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
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// A struct to represent a node in the queue
typedef struct node {
    void * data;
    struct node * tail;
} node;

// A struct to represent the whole queue. Contains a pointer to the front and
// back of the queue so that enqueue and dequeue operations both take constant
// time. Also holds the size of the queue so that operation is also constant
// time.
// This struct can be in 3 different states at a time.
// 1. If the queue is empty than the head and back pointers will be NULL and
//  size will be 0.
// 2. If the queue has 1 element than the head and back pointers will both
//  point to the start of the queue and size will be 1.
// 3. If the queue has more than 1 element than the head will point to the
//  beginning of the queue and the back will point to the end of the queue
//  with n - 2 elements in between them.
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

void que_enqueue( QueueADT queue, void * data ){
    node * new_node = (node*)malloc( sizeof( struct node ) );
    new_node->data = data;
    new_node->tail = NULL;
    if( queue->back != NULL ){
        queue->back->tail = new_node;
        queue->back = new_node;
    } else {
        queue->head = new_node;
        queue->back = new_node;
    }
    queue->size++;//increment size
}

void * que_dequeue( QueueADT queue ){
    if( queue->size == 0 ){//if size is 0 there is no element to dequeue
        fprintf( stderr, "Attempt to dequeue element that does not exist");
        exit( 0 );
    }

    void * data = queue->head->data;
    if( queue->size == 1 ){
        free( queue->head );
        queue->head = NULL;
        queue->back = NULL;
    } else {
        node * temp = queue->head->tail;
        free( queue->head );
        queue->head = temp;
    }
    queue->size--;//decrement size
    return data;
}

bool que_empty( QueueADT queue ){
    return queue->size == 0;
}

int queue_size( QueueADT queue ){
    return queue->size;
}
