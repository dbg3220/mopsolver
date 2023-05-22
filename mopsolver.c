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
#include <stdbool.h>
#include <assert.h>

#include "QueueADT.h"
#include "print_help.h"

#define BLOCKED  '#'
#define PASSABLE '.'
#define PATH     '+'

// Characters to signify predecessor cells in the maze
#define UP       'U'
#define DOWN     'D'
#define LEFT     'L'
#define RIGHT    'R'

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

/// Struct to represent a location in the maze
typedef struct Cell {
    unsigned short row;
    unsigned short col;
} Cell;

/// Helper function to create a cell.
/// @param row The row of the cell
/// @param col The column of the cell
/// @return The created cell
Cell * create_cell( unsigned short row, unsigned short col ){
    Cell * cell = (Cell*)malloc( sizeof( struct Cell ) );
    cell->row = row;
    cell->col = col;
    return cell;
}

/// Solves the maze with a breadth first search algorithm. Modifies the char
///  matrix given as the maze to include the solution path. Uses structs to
///  represent cells and their ancestors.
///
/// @param rows  The amount of rows in the maze
/// @param cols  The amount of columns in the maze
/// @param maze  A pointer to a char matrix representing the maze
/// @param display  true if the solver should reconstruct the path visually
/// @return The amount of moves taken to solve the maze, -1 if a solution does
///  not exist
int solve( int rows, int cols, char ** maze, bool display ) {
    QueueADT queue = que_create();// for the BFS
    QueueADT processed_cells = que_create();// to keep track of processed cells
    bool solution_found = false;
    if( maze[0][0] == PASSABLE ){
        maze[0][0] = LEFT;
        Cell * initial  = create_cell( 0, 0 );
        que_enqueue( queue, (void*) initial );
    }
    while( !que_empty( queue ) ) {
        Cell * current = (Cell*)que_dequeue( queue );
        unsigned short current_row = current->row;
        unsigned short current_col = current->col;

        if( current_row == rows - 1 && current_col == cols - 1 ){
            solution_found = true;
            free( current );
            break;
        }

        if( current_row != 0 &&
            maze[current_row - 1][current_col] == PASSABLE ){//north
            maze[current_row - 1][current_col] = DOWN;
            Cell * new_cell = create_cell( current_row - 1, current_col );
            que_enqueue( queue, (void*) new_cell );
        }
        if( current_row != rows - 1 &&
            maze[current_row + 1][current_col] == PASSABLE ){//south
            maze[current_row + 1][current_col] = UP;
            Cell * new_cell = create_cell( current_row + 1, current_col );
            que_enqueue( queue, (void*) new_cell );
        }
        if( current_col != 0 &&
            maze[current_row][current_col - 1] == PASSABLE ){//west
            maze[current_row][current_col - 1] = RIGHT;
            Cell * new_cell = create_cell( current_row, current_col - 1);
            que_enqueue( queue, (void*) new_cell );
        }
        if( current_col != cols - 1 &&
            maze[current_row][current_col + 1] == PASSABLE ){//east
            maze[current_row][current_col + 1] = LEFT;
            Cell * new_cell = create_cell( current_row, current_col + 1 );
            que_enqueue( queue, (void*) new_cell );
        }

        que_enqueue( processed_cells, current );
    }

    while( !que_empty( queue ) ){
        void * data = que_dequeue( queue );
        free( data );
    }
    que_destroy( queue );
    while( !que_empty( processed_cells ) ){
        void * data = que_dequeue( processed_cells );
        free( data );
    }
    que_destroy( processed_cells );

    if( !solution_found ){
        return -1;
    } else {//work backwards to find the path
        int steps = 1;
        Cell current = { rows - 1, cols - 1 };
        while( !(current.row == 0 && current.col == 0) ){
            steps++;
            switch( maze[current.row][current.col] ){
                case UP:
                    maze[current.row][current.col] = PATH;
                    current.row--;
                    break;
                case DOWN:
                    maze[current.row][current.col] = PATH;
                    current.row++;
                    break;
                case LEFT:
                    maze[current.row][current.col] = PATH;
                    current.col--;
                    break;
                case RIGHT:
                    maze[current.row][current.col] = PATH;
                    current.col++;
                    break;
            }
        }
        maze[0][0] = PATH;

        if( display ){// remove other characters for a clean maze path
            for( int i = 0; i < rows; i++ ){
                for( int j = 0; j < cols; j++){
                    char current = maze[i][j];
                    if( current == UP || current == DOWN ||
                        current == LEFT || current == RIGHT ){
                        maze[i][j] = PASSABLE;
                    }
                }
            }
        }

        return steps;
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

/// Takes a file stream as input and parses a text representation of a maze
///  into a matrix of chars.
///
/// @param input  The stream that the maze will be received from
/// @param rows  A pointer to an int that will be set to the amount of rows in
///  the maze
/// @param cols  A pointer to an int that will be set to the amount of columns
///  in the maze
/// @param maze  A double pointer char that this function will parse the maze
///  into
void parse( FILE * input, int * rows, int * cols, char *** maze ){
    int size = 120;
    int count = 0;
    *maze = (char**)malloc( sizeof( char* ) * size );
    char * buf = NULL;
    size_t n = 0;
    while( getline( &buf, &n, input ) != -1 ){
        char * line = (char*)malloc( sizeof( char ) * ( strlen( buf ) + 1 ) );
        count++;
        strcpy( line, buf );
        int columns = get_columns( line );
        if( count == 1 ){
            *cols = columns;
        }
        if( count > size ){
            size = size * 2;
            *maze = (char**)realloc( *maze, sizeof( char * ) * size ); 
        }
        (*maze)[count - 1] = (char*)malloc( sizeof( char ) * columns );
        for( int i = 0; i < columns; i++ ){
            if( line[i * 2] == '0' ){
                (*maze)[count - 1][i] = PASSABLE;
            }else{
                (*maze)[count - 1][i] = BLOCKED;
            }
        }
        free( line );
    }
    free( buf );
    *rows = count;
}

/// Main function for this program. Takes in flag command-line arguments
///  and solves a maze according to specified parameters.
///
/// @param argv  The number of given arguments
/// @param argc  An array of pointers to each argument
int main( int argv, char* argc[] ){
    char * infile = NULL;
    char * outfile = NULL;
    bool display_original = false;
    bool path_size = false;
    bool display_path = false;
    int opt;
    while( ( opt = getopt( argv, argc, "hdspi:o:" ) ) != -1 ){
        switch( opt ){
            case 'h':
                fprint_help( stdout );
                return EXIT_SUCCESS;
            case 'd':
                display_original = true;
                break;
            case 's':
                path_size = true;
                break;
            case 'p':
                display_path = true;
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
    
    int rows, cols;
    char ** maze = NULL;
    parse( input, &rows, &cols, &maze );

    if( display_original ){
        fpretty_print( output, rows, cols, maze );
    }

    int steps = solve( rows, cols, maze, display_path ); 

    if( path_size ){
        if( steps == -1 ){
            fprintf( output, "No solution.\n" );
        }else{
            fprintf( output, "Solution in %d steps.\n", steps );
        }
    }
    if( display_path ){
        fpretty_print( output, rows, cols, maze );
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

