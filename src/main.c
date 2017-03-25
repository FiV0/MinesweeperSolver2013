#include <time.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "gtk_minesweeper_solver.h"

int main(int argc,char * argv[]){
	srand(time(NULL));	
    gtk_init (&argc, &argv);
	
	minesweeper_solver();	

	return 0;
}
