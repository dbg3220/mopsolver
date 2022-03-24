//
// File: mopsolver.c
// Description: source module for solving and pretty-printing mazes
//
// @author Damon Gonzalez
// 
// @date 3/8/2022
//

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h> //temporary
#include <assert.h>

#include "QueueADT.h"
#include "print_help.h"

#define BLOCKED  '#'
#define PASSABLE '.'
#define PASSED   '+'

#define MAX_FILENAME 100

/// Structure representing a cell for use in the breadth-first search algorithm
typedef struct Cell_H {
    struct Cell_H * ancestor;
    short row;
    short column;
} * Cell;

/// Destroys a char matrix allocated on the heap
///
/// @param rows  The amount of rows in the matrix
/// @param cols  The amount of columns in the matrix
/// @param maze  The matrix to be destroyed
void destroy_matrix( int rows, void ** matrix ){
    for( int i = 0; i < rows; i++ ){
        free( matrix[i] );
    }
    free( matrix );
}

/// Creates a Cell_H object with a given Cell_H ancestor and given coordinates and
///  returns a pointer to it.
///
/// @param row  The row of the cell to create
/// @param col  The column of the cell to create
/// @return A pointer to the created cell
Cell create_cell( short row, short column, Cell ancestor ){
    Cell cell = (Cell)malloc( sizeof( struct Cell_H ) );
    cell->ancestor = ancestor;
    cell->row = row;
    cell->column = column;
    return cell;
}

/// Solves the maze with a breadth first search algorithm. Modifies the char
///  matrix given as the maze to include the solution path. Uses structs to
///  represent cells and their ancestors.
///
/// @param rows  The amount of rows in the maze
/// @param cols  The amount of columns in the maze
/// @param maze  A pointer to a char matrix representing the maze
/// @return The amount of moves taken to solve the maze, -1 if a solution does
///  not exist
int solve( int rows, int cols, char ** maze ){
    Cell entrance = create_cell( 0, 0, NULL );
    Cell solution = NULL;
    bool ** visited;
    visited = (bool**)malloc( sizeof( bool* ) * rows );
    for( int i = 0; i < rows; i++ ){
        visited[i] = (bool*)malloc( sizeof( bool ) * cols );
    }
    for( int i = 0; i < rows; i++ ){
        for( int j = 0; j < cols; j++ ){
            visited[i][j] = false;
        }
    }
    QueueADT all_cells = que_create( NULL );
    QueueADT queue = que_create( NULL );
    que_insert( all_cells, entrance );
    que_insert( queue, entrance );
    while( !que_empty( queue ) ){
        Cell current = (Cell)que_remove( queue );
        short current_row = current->row;
        short current_col = current->column;
        if( current_row == rows - 1 && current_col == cols - 1 ){
            solution = current;
            destroy_matrix( rows, (void**)visited );
            que_destroy( queue );
            break;
        }
        Cell child;
        if( current_row != 0 && 
            !visited[current_row - 1][current_col] &&
            maze[current_row - 1][current_col] != BLOCKED ){
            visited[current_row - 1][current_col] = true;
            child = create_cell( current_row - 1, current_col, current );
            que_insert( queue, child );
            que_insert( all_cells, child );
        }
        if( current_row != rows - 1 && 
            !visited[current_row + 1][current_col] &&
            maze[current_row + 1][current_col] != BLOCKED ){
            visited[current_row + 1][current_col] = true;
            child = create_cell( current_row + 1, current_col, current );
            que_insert( queue, child );
            que_insert( all_cells, child );
        }
        if( current_col != 0 && 
            !visited[current_row][current_col - 1] &&
            maze[current_row][current_col - 1] != BLOCKED ){
            visited[current_row][current_col - 1] = true;
            child = create_cell( current_row, current_col - 1, current );
            que_insert( queue, child );
            que_insert( all_cells, child );
        }
        if( current_col != cols - 1 &&
            !visited[current_row][current_col + 1] &&
            maze[current_row][current_col + 1] != BLOCKED ){
            child = create_cell( current_row, current_col + 1, current );
            que_insert( queue, child );
            que_insert( all_cells, child );
        }
    }
    if( solution != NULL ){
        int steps = 0;
        Cell current = solution;
        while( current != NULL ){
           maze[current->row][current->column] = PASSED; 
           current = current->ancestor;
           steps++;
        }
        while( !que_empty( all_cells ) ){
            Cell cell = (Cell)que_remove( all_cells );
            free( cell );
        }
        que_destroy( all_cells );
        return steps;      
    }else{
        return -1;
    }
}

/// Counts the number of 0s or 1s in a single string and gives that value
///
/// @param line  The string to be counting through
/// @return  The number of columns in the string, if interpreted as a row of a
///  maze
int get_columns( char * line ){
    int cols = 0;
    for( size_t i = 0; i < strlen( line ); i++ ){
        if( line[i] == '0' || line[i] == '1' ){
            cols++;
        }
    }
    return cols;
}

/// Parse a QueueADT of C strings into a char matrix and deletes the queue from
///  memory.
///
/// @param queue  The queue of strings that represent the mazes
/// @param int rows  The amount of rows in the maze
/// @param int cols  The amount of cols in the maze
/// @param maze  The char matrix that will be modified to represent the maze
/// 
/// @postcondition queue is empty
void parse( QueueADT queue, int cols, char ** maze ){
    int current_row = 0;
    while( !que_empty( queue ) ){
        char * line = (char*)que_remove( queue );
        for( int i = 0; i < cols; i++ ){
            if( line[i * 2] == '0' ){
                maze[current_row][i] = PASSABLE;
            }else{
                maze[current_row][i] = BLOCKED;
            }
        }
        free( line );
        current_row++;
    }
}

/// Main function for this program. Takes in flag command-line arguments
///  and solves a maze according to specified parameters.
///
/// @param argv  The number of given arguments
/// @param argc  An array of pointers to each argument
int main( int argv, char* argc[] ){
    char * infile = NULL;
    char * outfile = NULL;
    bool display = false;
    bool path_size = false;
    bool path = false;
    int opt;
    while( ( opt = getopt( argv, argc, "hdspi:o:" ) ) != -1 ){
        switch( opt ){
            case 'h':
                fprint_help( stdout );
                return EXIT_SUCCESS;
            case 'd':
                display = true;
                break;
            case 's':
                path_size = true;
                break;
            case 'p':
                path = true;
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
                fprint_help( stderr );
                return EXIT_SUCCESS;
        }
    }

    FILE * input = NULL;
    FILE * output = NULL;

    if( infile != NULL ){
        input = fopen( infile, "r" );
        free( infile );
    }else{
        input = stdin;
    }

    if( outfile != NULL ){
        output = fopen( outfile, "w" );
        free( outfile );
    }else{
        output = stdout;
    }
    
    assert( input != NULL );
    
    QueueADT lines = que_create( NULL );
    char * buf = NULL;
    size_t n = 0;
    while( getline( &buf, &n, input ) > 0 ){
        char * line = (char*)malloc( sizeof( char ) * ( strlen( buf ) + 1 ) );
        strcpy( line, buf );
        line[strlen(line) - 1] = '\0';
        que_insert( lines, (void*)line );
    }
    int rows = (int)que_size( lines );
    int cols = get_columns( buf );
    free( buf );

    char ** maze;
    maze = (char**)malloc( sizeof( char* ) * rows );
    for( int i = 0; i < rows; i++ ){
        maze[i] = (char*)malloc( sizeof( char ) * cols );
    }
    parse( lines, cols, maze );
    que_destroy( lines );
    
    if( display ){
        pretty_print( rows, cols, maze );
    }

    int steps = solve( rows, cols, maze ); 

    if( path_size ){
        if( steps == -1 ){
            printf( "No solution.\n" );
        }else{
            printf( "Solution in %d steps.\n", steps );
        }
    }
    if( path ){
        pretty_print( rows, cols, maze );
    }

    destroy_matrix( rows, (void**)maze );

    if( input != stdin ){
        fclose( input );
    }
    if( output != stdout ){
        fclose( output );
    }

    return EXIT_SUCCESS;
}

