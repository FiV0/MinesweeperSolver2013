#include <stdio.h>

#include "testing.h"

void read_data(char * c, field * f){
	int xdim, ydim, nbMines,value;
	char * buffer=malloc(1024*sizeof(char));
	char * tmp;
	int boolean=0,i,j;
	FILE * stream=fopen(c,"r");
	fscanf(stream,"xdim %d\nydim %d\nnbMines %d\n", &xdim, &ydim, &nbMines);
	f->x=xdim+2;
	f->y=ydim+2;
	f->nbMines=nbMines;
	f->display=malloc(f->x*f->y*sizeof(char));
	f->area=malloc(f->x*f->y*sizeof(char));
	for(i=0;i<f->x*f->y;i++){
		f->display[i]=1;
	}
	i=1;
	while(fgets(buffer,1024,stream) && !feof(stream)){
		if(i>xdim){
			i=1;
			boolean=1;
		}
		j=1;
		tmp=(char*)strtok(buffer," \n");
		if(boolean==0){
			while(tmp!=NULL){
				value=atoi(tmp);
				f->display[i*f->y+j]=(char)value;
				j++;
				tmp=(char*)strtok(NULL," \n");
			}
		}else{
			while(tmp!=NULL){
				value=atoi(tmp);
				f->area[i*f->y+j]=(char)value;
				j++;
				tmp=(char*)strtok(NULL," \n");
			}
		}
		i++;
	}
	free(buffer);
	fclose(stream);
}
