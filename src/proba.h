/**
@file proba.h
Although this file is called proba.h for probability, there is not a lot of 
probability in it. A minesweeper game can of course by analyzed and solved with
probability, but as the game grows this gets computationally very taxing.
That is the reason the module is rather a heuristique one. Meaning it rather
calculates the contributation of useful information which will be revealed
if opening a square than the actual probability of containing a mine.
*/
#ifndef _PROBA_H
#define _PROBA_H

#include "field.h"

/**
@brief random_square
calculates a square that seems to contain a lot of information and is rather less
likely to contain a mine. This function does NOT calculate the exact probability
but rather uses a heuristique method.
@param [in] f pointer to field
@param [in,out] pr pointer to position
*/
int random_square(const field * f,position *pr);

#endif
