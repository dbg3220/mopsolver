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

void print_help_stdout(){
    fprintf( stdout, HELP );
}

void print_help_stderr(){
    fprintf( stderr, HELP );
}
