/** 
@file imageRecognition.h
This module deals essentially with reconizing the minefield in a screenshot
and generating the clicks deduced by the solver at the correct positions.
*/
#ifndef _IMAGE_RECOGNITION
#define _IMAGE_RECOGNITION

#define round(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5)) 

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "field.h"

/** 
@brief  
The minefield contains a field in which all the game information is stored.
x_left and y_left are together the pixel-coordinates of the top left
corner of the minefield in the screenshot. x_old and y_old give information
about the last click generated while solving. This is used to interrupt 
the solving if the user moves his or her mouse. Square_size contains 
the average pixel length of a square.
*/
typedef struct {
	int x_left;
	int y_top;
	int x_old;
	int y_old;
	float square_size;
	field *fi;
}minefield;

/**
@brief calibrating
calcultes the top left corner and the square_size of a minefield and
expects a click from the user when called.
@param [in,out] mf pointer to minefield
@param [in] xsize x dimension of field. It has to passed as 
an argument because the field might not yet intialized
@returns an ErrorCode  	1 on succes
						-1 if an error occured loading the screenshot
						-2 if an error occured detecting the corner
						-3 if an error occured calculatin the square_size
*/
int calibrating(minefield *mf,int xsize);

/**
@brief init_recognition
intializes the field structure of the minefield.
@param [in,out] mf pointer to minefield
@param [in] xsize x dimension of field
@param [in] ysize y dimension of field
@param [in] nbMines number of mines in field
*/
void init_recognition(minefield* mf,int xsize, int ysize, int nbMines);

/**
@brief free_recognition
free the field of the minefield. Initialized with init_recognition.
@param [in,out] mf pointer to minefield
*/
void free_recognition(minefield *mf);

/**
@brief new_game
uses field_new_game te reset the field structure, but dimension do not 
change. x_old and y_old of the minefield are reset
@param [in,out] mf pointer to minefield
*/
void new_game(minefield *mf);

/**
@brief move_mouse_out
moves the mouse outside the minefield, so a screenshot can be taken 
and no errors occur when analizing the screenshot.
@param [in,out] mf pointer to minefield
*/
void move_mouse_out(minefield *mf);

/**
@brief read_field 
analyzes a screenshot and the respective squares of field in the
minefield.
@parma [in] screenshotpath pointer to string
@param [in,out] mf pointer to minefield
*/
int read_field(const char * screenshotpath, minefield * mf);

/**
@brief mouse_action
clicks at the respective position on the screen given a position.
@parma [in] p pointer to position
@param [in,out] mf pointer to minefield
*/
int mouse_action(const position * p,minefield * mf);

/**
@brief mouse_click_let_it_play
clicks at the pixel-coordinates passed as parameter.
@parma [in,out] mf pointer to minefield
@param [in] xcoord x coordinate of click
@param [in] ycoord y coordinate of click
*/
int mouse_click_let_it_play(minefield *mf,int xcoord,int ycoord);

#endif
