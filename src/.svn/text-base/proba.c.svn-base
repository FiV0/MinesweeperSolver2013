#include <time.h>
#include <glib.h>
#include <assert.h>

#include "field.h"
#include "proba.h"

/**
@brief square_best_adjaceny
calculates the number of mines closed in the adjaceny of a square that are sure
to not contain a mine.
@param [in] f pointer to field
@param [in] x integer 
@param [in] y integer
@return (closed squares in adjacency) - (value of square) + (flagged squares in adjacency)
*/
static int square_best_adjacency(const field *f, int x, int y){
	assert(get_state(f,x,y)==1);
	int i,j,v,undis=0,state;
	v=get_value(f,x,y);
	int xsize=field_get_xsize(f);
	int ysize=field_get_ysize(f);
	for(i=x-1;i<x+2;i++){
		for(j=y-1;j<y+2;j++){
			if(i>0 && j>0 && i<=xsize && j<=ysize){
				state=get_state(f,i,j);
				if(state==0){
					undis++;
				}
				if(state==2){
					v--;
				}
			}
		}
	}
	return undis-v;
}

/**
@brief open_in_adjacency
calculates the open squares in adjacency of a square that is closed
@param [in] f pointer to field
@param [in] x integer
@param [in] y integer
@return open squares in adjacency
*/
static int open_in_adjacency(const field *f,int x,int y){
	assert(get_state(f,x,y)==0);
	int i,j,open=0;
	int xsize=field_get_xsize(f);
	int ysize=field_get_ysize(f);
	for(i=x-1;i<x+2;i++){
		for(j=y-1;j<y+2;j++){
			if(i>0 && j>0 && i<=xsize && j<=ysize && (int)get_state(f,i,j)==1){
				open++;
			}
		}
	}
	return open;
}

int random_square(const field * f, position *pr){
	int i,j,ran,xsize,ysize;
	xsize=field_get_xsize(f);
	ysize=field_get_ysize(f);
	position p,p1;
	int undis=-1,currentundis;
	GArray *g=g_array_new(FALSE,FALSE,sizeof(position));
	for(i=1;i<=xsize;i++){
		for(j=1;j<=ysize;j++){
			if((int)get_state(f,i,j)==1 && (int)get_value(f,i,j)<5){
				currentundis=square_best_adjacency(f,i,j);	
				if(currentundis==undis){
					p.x=i;
					p.y=j;
					g_array_append_val(g,p);
				}
				if(currentundis>undis){
					g_array_free(g,TRUE);
					g=g_array_new(FALSE,FALSE,sizeof(position));
					p.x=i;
					p.y=j;
					g_array_append_val(g,p);
					undis=currentundis;
				}
			}
		}
	}
	if(undis==-1){
		pr->x=(rand()%f->x-3)+1;
		pr->y=(rand()%f->y-3)+1;
		pr->click=1;
		g_array_free(g,TRUE);
		return 1;
	}
	if(g->len==0){
		g_array_free(g,TRUE);
		g=g_array_new(FALSE,FALSE,sizeof(position));
		for(i=1;i<=xsize;i++){
			for(j=1;j<=ysize;j++){
				if((int)get_state(f,i,j)==1){
					p.x=i;
					p.y=j;
					g_array_append_val(g,p);
				}
			}
		}
		if(g->len=0){
			g_array_free(g,TRUE);
			return 0;
		}else{
			ran=(rand()%g->len);
			*pr=(position)g_array_index(g,position,ran);
			pr->click=1;
			return 1;
		}

	}
	GArray* g2=g_array_new(FALSE,FALSE,sizeof(position));
	int k,open=-1,currentopen;
	for(k=0;k<=g->len;k++){
		p=g_array_index(g,position,k);
		for(i=p.x-1;i<p.x+2;i++){
			for(j=p.y-1;j<p.y+2;j++){
				if(i>0 && j>0 && i<=xsize && j<=ysize && (int)get_state(f,i,j)==0 ){
					currentopen=open_in_adjacency(f,i,j);
					if(currentopen==open){
						p1.x=i;
						p1.y=j;
						g_array_append_val(g2,p1);
					}
					if(currentopen>open){
						g_array_free(g2,TRUE);
						g2=g_array_new(FALSE,FALSE,sizeof(position));
						p1.x=i;
						p1.y=j;
						g_array_append_val(g2,p1);
						open=currentopen;
					}
				}
			}
		}
	}
	ran=(rand()%g2->len);
	*pr=g_array_index(g2,position,ran);
	pr->click=1;
	g_array_free(g2,TRUE);
	g_array_free(g,TRUE);
	assert((pr->x)>0 && (pr->y)>0 && (pr->x)<=xsize && (pr->y)<=ysize);
	return 1;
}

