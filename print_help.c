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
void fpretty_print( FILE * stream, int rows, int cols, char ** path ){
    fprintf( stream, "|" );
    for( int i = 0; i < cols * 2 + 1; i++ ){
        fprintf( stream, "-" );
    }
    fprintf( stream, "|\n" );
    fprintf( stream, "  " );
    for( int i = 0; i < cols; i++ ){
        fprintf( stream, "%c ", path[0][i] );
    }
    fprintf( stream, "|\n" );
    for( int i = 1; i < rows - 1; i++ ){
        fprintf( stream, "| " );
        for( int j = 0; j < cols; j++ ){
            fprintf( stream, "%c ", path[i][j] );
        }
        fprintf( stream, "|\n" );
    }
    fprintf( stream, "| " );
    for( int i = 0; i < cols; i++ ){
        fprintf( stream, "%c ", path[rows - 1][i] );
    }
    fprintf( stream, " \n" );
    fprintf( stream, "|" );
    for( int i = 0; i < cols * 2 + 1; i++ ){
        fprintf( stream, "-" );
    }
    fprintf( stream, "|\n" );
}

