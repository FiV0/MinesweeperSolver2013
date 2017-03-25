#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "field.h"
#include <glib.h>
#include "solver.h"
#include "testing.h"

/**
@brief test.c
contains the main function for the debug version. The application should be called
as follows:
./debug textfile.txt
The application than tries to solve the minesweeper configuration stopping at
every iteration of the specified solver function.
*/
int main (int argc, char * argv[]){
	field f;
	int boolean=1;;
	read_data(argv[1],&f);
	while(!game_state(&f) && boolean)
	{
		display(&f);
		printf("\n");
		display_area(&f);
/*please comment out the solvers which you don't want to be used*/
/*		solver_single(&f);
		printf("field after single logic\n\n");
		display(&f);
		printf("\n");
		display_area(&f);
		solver_pair(&f);
		printf("field after pair logic\n\n");
		display(&f);
		printf("\n");
		display_area(&f);*/
		solver_pair_special(&f);
		printf("field after pair logic special\n\n");
		display(&f);
		printf("\n");
		display_area(&f);

		printf("Continue (0) no (1) yes\n ");
		scanf("%d", &boolean);
	}
	field_free(&f);
	return 0;
}	
