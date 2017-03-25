/**
@file screenInteraction.h
The module screenInteraction handles everything that is connected to 
the screen. It takes the screenshot,generates mouseclicks or gets the
current position of the cursor.
*/

#ifndef _SCREEN_INTERACTION
#define _SCREEN_INTERACTION


/** 
@brief mouse_click
generates a click at the pixel coordinates (x,y).
@param button Button1 for leftclick, Button3 for rightclick
@param [in] x x-coordinate of click
@param [in] y y-coordinate of click
*/
void mouse_click(int button,int x, int y);

/** 
@brief mouse_move
moves mouse to pixel coordinates (x,y)
@param [in] x x-coordinate
@param [in] y y-coordinate
*/
void mouse_move(int x, int y);

/**
@brief mouse_position
gets the current mouseposition coordinates.
@param [out] x pointer to x-coordinate
@param [out] y pointer to y-coordinate
*/
void mouse_position(int * x, int * y);

/** mouse_position_click
gets the mousepostion of a left or right button click.
@param button pointer to integer (Button1 for left, Button3 for right)
@param [out] x pointer to x-coordinate
@param [out] y pointer to y-coordinate
*/
void mouse_position_click(int* button,int * x, int * y);

/**
@brief screenshot
takes a sreenshot and stores it at the given path in the png format.
@param path pointer to string containing the path
*/
int screenshot(char * path);


#endif
