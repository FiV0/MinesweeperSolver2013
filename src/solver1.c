#include <time.h>
#include <assert.h> 

#include "field.h"
#include "logic.h"
#include "proba.h"
#include "solver1.h"

/* returns 1 when successfully solving the game 2 when mouse was moved 
3 on general success,but without fully solving,-4 on failure*/
int solver (minefield * mf,float timestamp){
	assert(timestamp>0);
	int count=0;
	int boolean=1;
	position p;
	float seconds;
	clock_t start,stop;	
	GArray * g=g_array_new(FALSE,FALSE,sizeof(position));
	while(boolean!=0){
		/*image recognition part*/
		move_mouse_out(mf);

		screenshot("screenshot.png");
		if(read_field("screenshot.png",mf)==0){
			screenshot("failed.png");
			printf("Error while reading minefield\n");
			g_array_free(g,TRUE);
			return -4;
		}

		single_logic(mf->fi,g);
		if(g->len==0){
			count++;
			pair_logic(mf->fi,g);
			if(g->len==0){
				count++;
				pair_logic_special(mf->fi,g);
				if(g->len==0)count++;
			}
		}
		if(g->len!=0)count=0;
		while(g->len!=0){

			start=clock();
			do{
				stop=clock();
				seconds = ((float)(stop-start)/(float)CLOCKS_PER_SEC);
			}while(seconds<timestamp);

			p=g_array_index(g,position,g->len-1);
			g_array_remove_index_fast(g,g->len-1);
			if((int)get_state(mf->fi,p.x,p.y)==0){
				if(!mouse_action(&p,mf)){
					g_array_free(g,TRUE);
					return 2;
				}
				if(p.click==2)set_state(mf->fi,p.x,p.y,2);
			}
		}
		if(count==3) boolean=0;
	}
	g_array_free(g,TRUE);
	if(game_state_reg(mf->fi))return 1;
	return 3;
}
/*maybe write this function a lot clearer
when leaving the normal solver we still need to implement part when the mouse was moved we don't random_square to be called
*/
int solver_proba(minefield * mf,float timestamp){
	assert(timestamp>0);
	float ts;
	if(timestamp<0.5){
			ts=0.5;
	}else{
			ts=timestamp;
	}
	int boolean=1,errorCode;
	float seconds;
	clock_t start,stop;	
	position p;
	while(boolean!=0){
		errorCode=solver(mf,timestamp);
		if(2<errorCode){
			if(random_square(mf->fi,&p)){

				/*printf("random square chosen x==%d y==%d\n",p.x,p.y);
				display(mf->fi);*/

				if(!mouse_action(&p,mf))boolean=0;

				start=clock();
				do{
					stop=clock();
					seconds = ((float)(stop-start)/(float)CLOCKS_PER_SEC);
				}while(seconds<ts);
				/*solve the fact that this doesn't work for small timestamps
				if I use a smaller */
			}	
		}else{
			return errorCode;
		}
	}
	return 1;
}

int solver_single (minefield * mf,float timestamp){
	assert(timestamp>0);
	int boolean=1;
	position p;
	float seconds;
	clock_t start,stop;	
	GArray * g=g_array_new(FALSE,FALSE,sizeof(position));
	while(boolean){
		/*image recognition part*/
		move_mouse_out(mf);

		screenshot("screenshot.png");
		if(read_field("screenshot.png",mf)==0){
			screenshot("failed.png");
			printf("Error while reading minefield\n");
			g_array_free(g,TRUE);
			return -4;
		}

		single_logic(mf->fi,g);
		if(g->len==0){
			boolean=0;
		}
		while(g->len!=0){

			start=clock();
			do{
				stop=clock();
				seconds = ((float)(stop-start)/(float)CLOCKS_PER_SEC);
			}while(seconds<timestamp);

			p=g_array_index(g,position,g->len-1);
			g_array_remove_index_fast(g,g->len-1);
			if((int)get_state(mf->fi,p.x,p.y)==0){
				if(!mouse_action(&p,mf))boolean=0;
				if(p.click==2)set_state(mf->fi,p.x,p.y,2);
			}
		}	
	}
	g_array_free(g,TRUE);
}

int solver_pair(minefield * mf,float timestamp){
	assert(timestamp>0);
	int boolean=1;
	position p;
	float seconds;
	clock_t start,stop;	
	GArray * g=g_array_new(FALSE,FALSE,sizeof(position));
	while(boolean){
		/*image recognition part*/
		move_mouse_out(mf);

		screenshot("screenshot.png");
		if(read_field("screenshot.png",mf)==0){
			screenshot("failed.png");
			printf("Error while reading minefield\n");
			g_array_free(g,TRUE);
			return -4;
		}

		pair_logic(mf->fi,g);
		if(g->len==0){
			boolean=0;
		}
		while(g->len!=0){

			start=clock();
			do{
				stop=clock();
				seconds = ((float)(stop-start)/(float)CLOCKS_PER_SEC);
			}while(seconds<timestamp);

			p=g_array_index(g,position,g->len-1);
			g_array_remove_index_fast(g,g->len-1);
			if((int)get_state(mf->fi,p.x,p.y)==0){
				if(!mouse_action(&p,mf))boolean=0;
				if(p.click==2)set_state(mf->fi,p.x,p.y,2);
			}
		}	
	}
	g_array_free(g,TRUE);
	return 1;
}

int solver_pair_special(minefield *mf,float timestamp){
	assert(timestamp>0);
	int boolean=1;
	position p;
	float seconds;
	clock_t start,stop;	
	GArray * g=g_array_new(FALSE,FALSE,sizeof(position));
	while(boolean){
		/*image recognition part*/
		move_mouse_out(mf);

		screenshot("screenshot.png");
		if(read_field("screenshot.png",mf)==0){
			screenshot("failed.png");
			printf("Error while reading minefield\n");
			g_array_free(g,TRUE);
			return -4;
		}

		pair_logic_special(mf->fi,g);
		if(g->len==0){
			boolean=0;
		}
		while(g->len!=0){

			start=clock();
			do{
				stop=clock();
				seconds = ((float)(stop-start)/(float)CLOCKS_PER_SEC);
			}while(seconds<timestamp);

			p=g_array_index(g,position,g->len-1);
			g_array_remove_index_fast(g,g->len-1);
			if((int)get_state(mf->fi,p.x,p.y)==0){
				if(!mouse_action(&p,mf))boolean=0;
				if(p.click==2)set_state(mf->fi,p.x,p.y,2);
			}
		}	
	}
	g_array_free(g,TRUE);
	return 1;
}

