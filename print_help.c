//
// File: print_help.c
// Description: source code to imkplement functions declared in print_help.h
//
// @author Damon Gonzalez
//
// @date 3/9/2022
//

#include <stdio.h>

#include "print_help.h"

/// Prints the standard usage messae to a provided output stream
void fprint_help( FILE * output ){
    fprintf( output, HELP );
}

/// Pretty prints a maze
void pretty_print( int rows, int cols, char ** path ){
    printf( "|" );
    for( int i = 0; i < cols * 2 + 1; i++ ){
        printf( "-" );
    }
    printf( "|\n" );
    printf( "  " );
    for( int i = 0; i < cols; i++ ){
        printf( "%c ", path[0][i] );
    }
    printf( "|\n" );
    for( int i = 1; i < rows - 1; i++ ){
        printf( "| " );
        for( int j = 0; j < cols; j++ ){
            printf( "%c ", path[i][j] );
        }
        printf( "|\n" );
    }
    printf( "| " );
    for( int i = 0; i < cols; i++ ){
        printf( "%c ", path[rows - 1][i] );
    }
    printf( " \n" );
    printf( "|" );
    for( int i = 0; i < cols * 2 + 1; i++ ){
        printf( "-" );
    }
    printf( "|\n" );
}

