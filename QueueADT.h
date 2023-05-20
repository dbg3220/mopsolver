// File: QueueADT.h
//
// Description:  Interface to the QueueADT module
//
// Author:  CS@RIT.EDU
// Author:  Damon Gonzalez
//

#ifndef _QUEUEADT_H_
#define _QUEUEADT_H_

#include <stdbool.h>

// Define QueueADT type ONLY IF _not_ compiling the module implementation file.
//
// In the implementation file, define the QueueADT type as you need
// to for the implementation, and then define the symbol _QUEUE_IMPL_
// immediately before including this header file to prevent a
// redefinition of the type.
//

#ifndef _QUEUE_IMPL_

/// QueueADT is a pointer to an abstract queue data structure whose
/// payload data type is opaque, its internals are kept private

typedef struct QueueStruct * QueueADT;

#endif

/// Create a fifo QueueADT.
///
/// @return a QueueADT instance, or NULL if the allocation fails

QueueADT que_create();


/// Tear down and deallocate the supplied QueuADT.
///
/// @param queue - the QueueADT to be manipulated

void que_destroy( QueueADT queue );


/// Remove all contents from the supplied QueueADT.
///
/// @param queue - the QueueADT to be manipuated

void que_clear( QueueADT queue );


/// Enqueue an element to the end of the queue.
///
/// @param queue the QueueADT into which the value is to be inserted
/// @param data the data to be inserted
/// @exception If the value cannot be inserted into the queue for
///     whatever reason (usually implementation-dependent), the program
///     should terminate with an error message.  This can be done by
///     printing an appropriate message to the standard error output and
///     then exiting with EXIT_FAILURE, or by having an assert() fail.

void que_enqueue( QueueADT queue, void * data );


/// Dequeue an element from the front of the queue.
///
/// @param queue the QueueADT to be manipulated
/// @return the value that was removed from the queue
/// @exception If the queue is empty, the program should terminate
///     with an error message.  This can be done by printing an
///     appropriate message to the standard error output and then
///     exiting with EXIT_FAILURE, or by having an assert() fail.

void * que_dequeue( QueueADT queue );


/// Indicate whether or not the supplied Queue is empty
///
/// @param queue - the QueueADT to be tested
/// @return true if the queue is empty, otherwise false

bool que_empty( QueueADT queue );


/// Give the size of the queue at the current time.
///
/// @param queue - the QueueADT to be tested
/// @return The number of elements in the queue

int queue_size( QueueADT queue );

#endif

