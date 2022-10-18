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

/// struct for representing an element in the queue, contains a pointer to the
///  next element and a generic pointer to the data payload
typedef struct Element_H {
    void * data;
    struct Element_H * next;
} * Element;

/// object representation of a queue abstract data type
typedef struct QueueADT_H {
    Element first;
    int (*cmp)( const void * a, const void * b );
} * QueueADT;

#define _QUEUE_IMPL_
#include "QueueADT.h"

/// Creates a queue
QueueADT que_create( int (*cmp)( const void * a, const void * b ) ){
    QueueADT queue = (QueueADT)malloc( sizeof( struct QueueADT_H ) );
    queue->first = NULL;
    queue->cmp = cmp; 
    return queue;
}

/// Destroys a queue
void que_destroy( QueueADT queue ){
    que_clear( queue );
    free( queue );
}

/// Clears a queue of all elements
void que_clear( QueueADT queue ){
    Element elm = queue->first;
    queue->first = NULL;
    while( elm != NULL ){
        Element next = elm->next;
        free( elm );
        elm = next;
    }
}

/// Inserts an element into the queue
void que_insert( QueueADT queue, void * data ){
    Element new_elm = (Element)malloc( sizeof( struct Element_H ) );
    new_elm->data = data;
    new_elm->next = NULL;
    if( que_empty( queue ) ){
        queue->first = new_elm;
    }else{
        if( queue->cmp == NULL ){
            Element elm = queue->first;
            while( elm->next != NULL ){
                elm = elm->next;
            }
            elm->next = new_elm;
        }else{
            if( queue->cmp( data, queue->first->data ) < 0 ){
                new_elm->next = queue->first;
                queue->first = new_elm;
            }else{
                Element elm = queue->first;
                while( elm->next != NULL && 
                       !( queue->cmp( data, elm->next->data ) < 0 ) ){
                    elm = elm->next;                    
                }
                if( elm->next == NULL ){
                    elm->next = new_elm;
                }else{
                    new_elm->next = elm->next;
                    elm->next = new_elm;
                }
            }
        }
    }
}

/// Removes the first element in the queue
void * que_remove( QueueADT queue ){
    assert( !que_empty( queue ) );
    Element elm = queue->first;
    queue->first = elm->next;
    void * data = elm->data;
    free( elm );
    return data;
}

/// Returns true if queue is empty
bool que_empty( QueueADT queue ){
    return queue->first == NULL;
}

