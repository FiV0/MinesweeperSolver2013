/** 
@file field.h
This is the most basic module of the application. Field contains the information
about the minefield. There are two layers in the field. First there is the 'area'
which contains the actual information (called value later on) of each square (0-8 for a square without a mine
and -1 for a mine). The second layer, 'display', contains the informtion if a square has 
been opened(1), is closed(0) or if it has been marked with a flag(2) (called state later on). Other than that a field 
contains information about it's size (x and y) and the actual number of mines (nbMines) 
randomly distributed in the field. For the simplicity of some algorithms in the
application a border is added to each side of the field. So if we are playing a
game of minesweeper on a 9x9 board Field will actually contain a 11x11 board.
An example follows

display

-----------------> y dimesion

| 0 0 2 0 0

| 0 1 1 1 0

| 0 1 1 1 0

| 0 1 1 1 0

| 0 0 0 0 0 

v

x dimesion

area

-----------------> y dimesion

|-1 2-1 2-1

| 2 3 1 3 2

|-1 1 0 1-1

| 2 3 1 3 2

|-1 2-1 2-1 

v

x dimesion


what will be seen

-----------------> y dimesion

| * * # * *    

| * 3 1 3 *  

| * 1 0 1 *

| * 3 1 3 *

| * * * * *

v

x dimesion

where * is a closed square and # a flagged one
*/
#ifndef _FIELD_H
#define _FIELD_H

#include <assert.h>

/**
@brief position
is actually a structure not used in field, but it is used by many different modules and field is 
included in every other module so I put it here. It contains the postition of square (x,y) and
the information about the square. Click contains 1 if the square can be safely opened and 2 if
it can be flagged
*/
typedef struct {
	int x;
	int y;
	char click; /*1 left 2 right*/
}position;

typedef struct {
	char * area;
	char * display;
	int x;
	int y;
	int nbMines;
}field;

/**
@brief field_get_xsize
@param [in] f pointer to field
@return x dimension of the field
*/
int field_get_xsize(const field *f);

/**
@brief field_get_ysize
@param [in] f pointer to field
@return y dimension of the field
*/
int field_get_ysize(const field *f);

/**
@brief field_init
initializes a field with a minesweeper game of size x times y with the 
specified number of mines in it. Only used in the Terminal version.
@param [in,out] f pointer to field
@param [in] x integer
@param [in] y integer
@param [in] mines integer 
*/
void field_init(field * f, int x, int y, int mines);

/**
@brief field_init_version2
initializes a field for the final application. All squares except for the 
borders are set to closed. The borders are set to open.
@param [in,out] f pointer to field
@param [in] x integer
@param [in] y integer
@param [in] mines integer 
*/
void field_init_version2(field * f, int x, int y, int mines);

/**
@brief field_new_game
resets all the squares except for the borders to closed. 
This function is used if the dimensions
of the field have not changed but we want to start a new game.
@param [in,out] f pointer to field
*/
void field_new_game(field *f);

/**
@brief field_free
The memory allocated with field_init or field_init_version2 is freeed.
@param [in,out] f pointer to field
*/
void field_free(field * f);

/**
@brief get_state
returns the state of the square indicated.
@param [in] f pointer to field
@param [in] x integer 
@param [in] y integer
@return the state of the square (0 closed 1 open 2 flagged) at position
x (row) times y (column) in the field
*/
char get_state(const field * f,int x, int y);

/**
@brief set_state
Sets the state at position x (row) times y (column) to the given state.
@param [in] f pointer to field
@param [in] x integer 
@param [in] y integer
@param [in] state character
*/
void set_state(field *f, int x ,int y,char state);

/**
@brief get_value
returns the value of the square indicated.
@param [in] f pointer to field
@param [in] x integer 
@param [in] y integer
@return the value of the square (0-8 if no mine -1 if mine) at position
x (row) times y (column) in the field
*/
char get_value(const field * f, int x ,int y);

/**
@brief set_value
Sets the value at position x (row) times y (column) to the given value.
@param [in] f pointer to field
@param [in] x integer 
@param [in] y integer
@param [in] value character
*/
void set_value(field * f, int x, int y, char value);

/**
@brief discover
Opens a square at position x times y and if value is 0 it
will be recursivly called on the neighbours of the given square.
@param [in,out] f pointer to field
@param [in] x integer
@param [in] y integer
*/
void discover(field * f,int x,int y);

/**
@brief game_state
checks if a minesweeper game was lost. Only used in Terminal version.
@param [in] f pointer to field
@return integer -1 lost 1 won 0 still to go
*/
int game_state(const field * f);

/**
@brief game_state
checks if a minesweeper game was lost. Used if game is analysed via 
image recognition.
@param [in] f pointer to field
@return integer -1 lost 1 won 0 still to go
*/
int game_state_reg(const field *f);

/**
@brief display
displays the field in a terminal as shown above. Only used in Terminal and debug version.
@param [in] f pointer to field
*/
void display(const field * f);

/**
@brief display_area
displays the values of the area. Useful to test and debug a program. 
Only used in Terminal and debug version
*/
void display_area(const field * f);

/** 
@brief field_test
is test regression function for the field module.
*/
void field_test();

#endif
