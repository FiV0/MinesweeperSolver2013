#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "field.h"
#include <glib.h>
#include "solver.h"
/**
@file mainTerminal.c
Lets the user play a game of minesweeper in the terminal with help of
the logical solver. The application should be called as follows:
./Testing xdim ydim numberOfMines
*/
int main(int argc, char * argv[]){
	srand(time(NULL));
	field f;
	int xdim=atoi(argv[1]);
	int ydim=atoi(argv[2]);
	field_init(&f,xdim,ydim,atoi(argv[3]));
	int x,y;
	int sqOrFlag;
	int game=0;
	display(&f);
	while(game==0){
		display_area(&f);
		do{
			printf("Discover square(0) or set flag(1)\n");
			scanf("%d",&sqOrFlag);
		}while(sqOrFlag!=0 && sqOrFlag!=1);
		fflush(stdin);
		if(sqOrFlag==0){
			do{
				printf("Give the x and y coordinate of the square to discover!\n");
				scanf("%d %d",&x,&y);
			}while(x<1 || y<1 || x>xdim || y>ydim || get_state(&f,x,y)==1);
			set_state(&f,x,y,1);
			if((int)get_value(&f,x,y)==0){
				discover(&f,x,y);
			}

			printf("Discover called\n");
			display(&f);
			printf("\n");
			display_area(&f);
			printf("\n");

		}else{
			do{
				printf("Give the x and y coordinate of the square where you want to set your flag!\n");
				scanf("%d %d",&x,&y);
			}while(x<1 || y<1 || x>xdim || y>ydim || get_state(&f,x,y)==1);	
			set_state(&f,x,y,2);
		}
		fflush(stdin);
	
		solver(&f);
		
		printf("Field after solver\n");
		display(&f);
		printf("\n");
	
		
/*if only certain solving functions should be called the code should be modified
in thies section*/
	/*	solver_single(&f);
		
		printf("Field after single logic\n");
		display(&f);
		printf("\n");

		solver_pair(&f);

		printf("Field after pair logic\n");
		display(&f);
		printf("\n");*/

		game=game_state(&f);
	}
	if(game==1){
		printf("\nYou've won !!!\n");
	}else{
		printf("\nYou've lost :-(\n");
	}

	field_free(&f);	
	return 0;
}
