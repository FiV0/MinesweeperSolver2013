#include "solver.h"

void solver (field * f){
	int count=0;
	int boolean=1;
	position p;
	GArray * g=g_array_new(FALSE,FALSE,sizeof(position));
	while(boolean){
		single_logic(f,g);
		if(g->len==0){
			count++;
			pair_logic(f,g);
			if(g->len==0)count++;
		}
		if(g->len!=0)count=0;
		while(g->len!=0){
			p=g_array_index(g,position,g->len-1);
			g_array_remove_index_fast(g,g->len-1);
			set_state(f,p.x,p.y,p.click);
			if((int)get_value(f,p.x,p.y)==0){
				discover(f,p.x,p.y);
			}
		}
		if(count==2) boolean=0;
	}
	g_array_free(g,TRUE);
}

void solver_single (field * f){
	int boolean=1;
	position p;
	GArray * g=g_array_new(FALSE,FALSE,sizeof(position));
	while(boolean){
		single_logic(f,g);
		if(g->len==0){
			boolean=0;
		}
		while(g->len!=0){
			p=g_array_index(g,position,g->len-1);
			g_array_remove_index_fast(g,g->len-1);
			set_state(f,p.x,p.y,p.click);
			if((int)get_value(f,p.x,p.y)==0){
				discover(f,p.x,p.y);
			}
		}
	}
	g_array_free(g,TRUE);
}

void solver_pair(field * f){
	int boolean=1;
	position p;
	GArray * g=g_array_new(FALSE,FALSE,sizeof(position));
	while(boolean){
		pair_logic(f,g);
		if(g->len==0){
			boolean=0;
		}
		while(g->len!=0){
			p=g_array_index(g,position,g->len-1);
			g_array_remove_index_fast(g,g->len-1);
			set_state(f,p.x,p.y,p.click);
			if((int)get_value(f,p.x,p.y)==0){
				discover(f,p.x,p.y);
			}
		}
	}
	g_array_free(g,TRUE);
}

void solver_pair_special(field*f){
	int boolean=1;
	position p;
	GArray * g=g_array_new(FALSE,FALSE,sizeof(position));
	while(boolean){
		pair_logic_special(f,g);
		if(g->len==0){
			boolean=0;
		}
		while(g->len!=0){
			p=g_array_index(g,position,g->len-1);
			g_array_remove_index_fast(g,g->len-1);
			set_state(f,p.x,p.y,p.click);
			if((int)get_value(f,p.x,p.y)==0){
				discover(f,p.x,p.y);
			}
		}
	}
	g_array_free(g,TRUE);
}

