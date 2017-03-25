/**
@file  logic.h
Logic is the module that searches for certain patterns in the minefield 
and deduces squares that can be safely opened or surely flagged.
The module does NOT find all logically possible patterns, but does in 
general a very good job.
*/
#ifndef _LOGIC_H
#define _LOGIC_H

#include <glib.h>
#include "field.h"

/*
@brief single_logic
only looks at squares individually and deduces squares that can be
opened or flagged in the immediate adjaceny. The deduced squares are
stored in the GArray with the respective click.
@param [in] f pointer to field
@param [in,out] g pointer to GArray
*/
void single_logic(const field * f, GArray * g);

/*
@brief pair_logic
looks at two adjacent open squares and deduces squares that can be
opened or flagged in the immediate adjaceny. The deduced squares are
stored in the GArray with the respective click.
@param [in] f pointer to field
@param [in,out] g pointer to GArray
*/
void pair_logic(const field * f, GArray * g);

/*
@brief pair_logic_special
looks at two adjacent open squares and deduces squares that can be
opened or flagged in the immediate adjaceny. This procedure covers
some special cases which are not dealt with in pair_logic.
The deduced squares are stored in the GArray with the respective click.
@param [in] f pointer to field
@param [in,out] g pointer to GArray
*/
void pair_logic_special(const field *f, GArray *g);

#endif

