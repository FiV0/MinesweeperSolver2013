/**
@file solver1.h
This module puts all the different modules like screenInteraction,
imageRecognition, proab and logic together to create the actual solver.
*/
#ifndef _SOLVER1_H
#define _SOLVER1_H

#include "imageRecognition.h"

/**
@brief solver
tries to solve a game logically.
@param mf pointer to minefield
@param timestamp in seconds as float
*/
int solver(minefield * mf,float timestamp);

/**
@brief solver_proba
tries to solve a game with solver and random_square.
Will fail or succeed if not interrupted.
@param mf pointer to minefield
@param timestamp in seconds as float
*/
int solver_proba(minefield * mf, float timestamp);

/**
@brief solver_single
tries to solve a game logically only using single_logic.
@param mf pointer to minefield
@param timestamp in seconds as float
*/
int solver_single(minefield * mf,float timestamp);

/**
@brief solver
tries to solve a game logically only using pair_logic.
@param mf pointer to minefield
@param timestamp in seconds as float
*/
int solver_pair(minefield *mf,float timestamp);

/**
@brief solver
tries to solve a game logically only using pair_logic_special.
@param mf pointer to minefield
@param timestamp in seconds as float
*/
int solver_pair_special(minefield *mf,float timestamp);

#endif
