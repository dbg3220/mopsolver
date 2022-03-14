//
// File: mopsolver.c
// Description: source module for solving and pretty-printing mazes
//
// @author Damon Gonzalez
// 
// @date 3/8/2022
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "print_help.h"

#define BLOCKED  '#'
#define PASSABLE '.'
#define PASSED   '+'

#define MAX_FILENAME 100

/// Reads a valid maze from given input
///
/// @param input  An input stream provided
/// @param rows  The amount of rows of the maze
/// @param cols  The amount of cols of the maze
/// @param maze  A char array that will contain a character representation of
///  the maze after this function is done
void parse_maze( FILE * input, int rows, int cols, char maze[rows][cols] ){
    char str[200];
    fgets( str, 200, input );
    maze[0][0] = BLOCKED;
}

/// Solves the maze with a breadth first search algorithm
///
/// @param TODO
/// @return The amount of moves taken to solve the maze
int solve(){
    return 0;
}

/// Main function for this program. Takes in flag command-line arguments
///  and solves a maze according to specified parameters.
///
/// @param argv  The number of given arguments
/// @param argc  An array of pointers to each argument
int main( int argv, char* argc[] ){
    char * infile = NULL;
    char * outfile = NULL;
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
                infile = (char*)malloc( strlen( optarg ) + 1 );
                strcpy( infile, optarg );
                break;
            case 'o':
                outfile = (char*)malloc( strlen( optarg ) + 1 );
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

    if( infile != NULL ){
        input = fopen( infile, "r" );
    }else{
        input = stdin;
    }

    if( outfile != NULL ){
        output = fopen( outfile, "w" );
    }else{
        output = stdout;
    }

    //TODO somewhere in here solve the maze
    
    if( input != stdin ){
        fclose( input );
    }

    if( output != stdout ){
        fclose( output );
    }

    return EXIT_SUCCESS;
}

