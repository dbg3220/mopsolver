//
// File: simple_graph.h
// Description: functions and defined error message string for printing errors
//  in the mopsolver program
//
// @author Damon Gonzalez
//
// @date 3/9/2022
//

#ifndef HELP_FILE
#define HELP_FILE

#define HELP    "Usage:\n"\
                "mopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n"\
                "Options:\n"\
                "  -h          Print usage and options list to stdout only.  "\
                "  (Default: off)\n"\
                "  -d          Pretty-print (display) the maze after reading."\
                "  (Default: off)\n"\
                "  -s          Print length of shortest path or 'No solution'"\
                ". (Default: off)\n"\
                "  -p          Pretty-print maze with the path, if one exists"\
                ". (Default: off)\n"\
                "  -i infile   Read maze from infile.                        "\
                "  (Default: stdin)\n"\
                "  -o outfile  Write all output to outfile.                  "\
                "  (Default: stdout)\n"\

/// Prints the standard usage message to standard output
void print_help_stdout();

/// Prints the standard usage message to standard error
void print_help_stderr();

#endif

