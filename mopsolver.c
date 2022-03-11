//
// File: mopsolver.c
// Description: source module for solving and pretty-printing mazes
//
// @author Damon Gonzalez
// 
// @date 3/8/2022
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "print_help.h"

#define BLOCKED  '#'
#define PASSABLE '.'

#define MAX_FILENAME 100

/// Main function for this program. Takes in flag command-line arguments
///  and solves a maze according to specified parameters.
///
/// @param argv  The number of given arguments
/// @param argc  An array of pointers to each argument
int main( int argv, char* argc[] ){
    char infile[MAX_FILENAME] = "";
    char outfile[MAX_FILENAME] = "";
    int d, s, p;
    int opt;
    while( ( opt = getopt( argv, argc, "hdspi:o:" ) ) != -1 ){
        switch( opt ){
            case 'h':
                print_help_stdout();
                return EXIT_SUCCESS;
            case 'd':
                d = 1;
                break;
            case 's':
                s = 1;
                break;
            case 'p':
                p = 1;
                break;
            case 'i':
                strcpy( infile, optarg );
                break;
            case 'o':
                strcpy( outfile, optarg );
                break;
            default:
                print_help_stderr();
                return EXIT_SUCCESS;
        }
    }
    FILE * input;
    FILE * output;

    if( d == 1 ){
        printf( "Display the initial maze\n" );
    }

    if( s == 1 ){
        printf( "Print length of shortest path\n" );
    }

    if( p == 1 ){
        printf( "Print the path, if it exists\n" );
    }

    if( strcmp( infile, "" ) != 0 ){
        printf( "An infile was provided: %s\n", infile );//returns NULL if unable to open file
        input = fopen( infile, "r" );
    }else{
        input = stdin;
    }

    if( strcmp( outfile, "" ) != 0 ){
        printf( "An outfile was provided: %s\n", outfile );
        output = fopen( outfile, "w" );
    }else{
        output = stdout;
    }

    //TODO somewhere in here solve the maze
    
    if( strcmp( infile, "" ) == 0 ){
        fclose( input );
    }

    if( strcmp( outfile, "" ) == 0 ){
        fclose( output );
    }

    return EXIT_SUCCESS;
}

