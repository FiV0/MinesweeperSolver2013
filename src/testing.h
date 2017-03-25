/**
@file testing.h
This module is only for the debug version. The module
permits to read a given minesweeper configuration from
a a text file. The format should be as follows:
xdim number
ydim number
nbMines number
display
area

Examples can be found in the tests directory.
*/

#ifndef _TESTING_H
#define _TESTING_H

#include "field.h"

/**
@brief read_data
reads data form a given file and stores it in the field structure.
@param c pointer to string (path to file)
@param f pointer to field
*/
void read_data(char * c, field * f);

#endif 
