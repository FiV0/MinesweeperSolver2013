#include "logic.h"

/** counts the number of undiscovered squares that is touching a uncovered square if the number of the square and the undiscoverd squares is matching, these squares must be mines.
*/

void single_logic (const field * f, GArray * g){
	int current,i,j,k,l,mines,number,xsize,ysize;
	xsize=field_get_xsize(f);
	ysize=field_get_ysize(f);
	position p;	
	for(i=1;i<=xsize;i++){
		for(j=1;j<=ysize;j++){
			if((int)get_state(f,i,j)==1 && (int)get_value(f,i,j)!=0){
				current=get_value(f,i,j);
				number=current;
				mines=0;
				for(k=i-1;k<i+2;k++){
					for(l=j-1;l<j+2;l++){
						if((int)get_state(f,k,l)!=1) current--;
						if((int)get_state(f,k,l)==2) mines++;
					}
				}
				if(current==0){
					for(k=i-1;k<i+2;k++){
						for(l=j-1;l<j+2;l++){
							if((int)get_state(f,k,l)==0){
								p.x=k;
								p.y=l;
								p.click=2;
								g_array_append_val(g,p);
							}
						}
					}
				}
				if(mines==number){
					for(k=i-1;k<i+2;k++){
						for(l=j-1;l<j+2;l++){
							if((int)get_state(f,k,l)==0){
								p.x=k;
								p.y=l;
								p.click=1;
								g_array_append_val(g,p);
							}
						}
					}
				}
			}
		}
	}
}

/** compares essentially the numbers of two neighboring discovered squares and deduces positions of mines or squares that are safe to discover. All more complicated cases of minesweeper configurations can be reduced to simpler cofigurations. This is essentially the what this fuction does.
This is the most essential function in the whole application.
*/
	
void pair_logic(const field * f,GArray * g){
	int current,i,j,k,l;
	int tmp,acc1,acc2;
	int up,down,left,right;
	int undis,xsize,ysize;
	xsize=field_get_xsize(f);
	ysize=field_get_ysize(f);
	position p;
	for(i=1;i<=xsize;i++){
		for(j=1;j<=ysize;j++){
			if(get_state(f,i,j)==1 && get_value(f,i,j)!=0){
				undis=0;
				current=get_value(f,i,j);
				for(k=i-1;k<i+2;k++){
					for(l=j-1;l<j+2;l++){
						tmp=get_state(f,k,l);
						if(tmp==2)current--;
						if(tmp==0)undis++;
					
					}
				}
				if(current>0 && current<3 && undis==3){
					if(current==1){
						p.click=1;
					}else{
						p.click=2;
					}
					if(j-1>0 && get_state(f,i,j-1)==1){
						left=get_value(f,i,j-1);
						for(k=i-1;k<i+2;k++){
							for(l=j-2;l<j+1;l++){
								if(get_state(f,k,l)==2)left--;
							}
						}
						if(left==1){
							acc1=0;
							acc2=0;
							for(k=-1;k<2;k++){
								if(get_state(f,i-1,j+k)==0)acc1++;
								if(get_state(f,i+1,j+k)==0)acc2++;
							}
							if(current==2){
								if(acc1==0 && acc2==3){
									p.x=i+1;
									p.y=j+1;
									g_array_append_val(g,p);
								}
								if(acc1==3 && acc2==0){
									p.x=i-1;
									p.y=j+1;
									g_array_append_val(g,p);
								}
							}else{
								if(acc1==0 && acc2==3 && (j-2<1 || (int)get_state(f,i+1,j-2)!=0)){
									p.x=i+1;
									p.y=j+1;
									g_array_append_val(g,p);
								}
								if(acc1==3 && acc2==0 && (j-2<1 || (int)get_state(f,i-1,j-2)!=0)){
									p.x=i-1;
									p.y=j+1;
									g_array_append_val(g,p);
								}
							}
						}
					}
					if(j+1<f->y-1 && get_state(f,i,j+1)==1){
						right=get_value(f,i,j+1);
						for(k=i-1;k<i+2;k++){
							for(l=j;l<j+3;l++){
								if(get_state(f,k,l)==2)right--;
							}
						}
						if(right==1){
							acc1=0;
							acc2=0;
							for(k=-1;k<2;k++){
								if(get_state(f,i-1,j+k)==0)acc1++;
								if(get_state(f,i+1,j+k)==0)acc2++;
							}
							if(current==2){
								if(acc1==0 && acc2==3){
									p.x=i+1;
									p.y=j-1;
									g_array_append_val(g,p);
								}
								if(acc1==3 && acc2==0){
									p.x=i-1;
									p.y=j-1;
									g_array_append_val(g,p);
								}
							}else{
								if(acc1==0 && acc2==3 && (j+2>=ysize+1 || (int)get_state(f,i+1,j+2)!=0)){
									p.x=i+1;
									p.y=j-1;
									g_array_append_val(g,p);
								}
								if(acc1==3 && acc2==0 && (j+2>=ysize+1 || (int)get_state(f,i-1,j+2)!=0)){
									p.x=i-1;
									p.y=j-1;
									g_array_append_val(g,p);
								}
							}
						}
					}
					if(i-1>0 && get_state(f,i-1,j)==1){
						up=get_value(f,i-1,j);
						for(k=i-2;k<i+1;k++){
							for(l=j-1;l<j+2;l++){
								if(get_state(f,k,l)==2)up--;
							}
						}
						if(up==1){
							acc1=0;
							acc2=0;
							for(k=-1;k<2;k++){
								if(get_state(f,i+k,j-1)==0)acc1++;
								if(get_state(f,i+k,j+1)==0)acc2++;
							}
							if(current==2){
								if(acc1==0 && acc2==3){
									p.x=i+1;
									p.y=j+1;
									g_array_append_val(g,p);
								}
								if(acc1==3 && acc2==0){
									p.x=i+1;
									p.y=j-1;
									g_array_append_val(g,p);
								}
							}else{
								if(acc1==0 && acc2==3 && (i-2<1 || (int)get_state(f,i-2,j+1)!=0)){
									p.x=i+1;
									p.y=j+1;
									g_array_append_val(g,p);
								}
								if(acc1==3 && acc2==0 && (i-2<1 || (int)get_state(f,i-2,j-1)!=0)){
									p.x=i+1;
									p.y=j-1;
									g_array_append_val(g,p);
								}
							}
						}
					}
					if(i+1<f->x-1 && get_state(f,i+1,j)==1){
						down=get_value(f,i+1,j);
						for(k=i;k<i+3;k++){
							for(l=j-1;l<j+2;l++){
								if(get_state(f,k,l)==2)down--;
							}
						}
						if(down==1){
							acc1=0;
							acc2=0;
							for(k=-1;k<2;k++){
								if(get_state(f,i+k,j-1)==0)acc1++;
								if(get_state(f,i+k,j+1)==0)acc2++;
							}
							if(current==2){
								if(acc1==0&&acc2==3){
									p.x=i-1;
									p.y=j+1;
									g_array_append_val(g,p);
								}
								if(acc1==3 && acc2==0){
									p.x=i-1;
									p.y=j-1;
									g_array_append_val(g,p);
								}
							}else{
								if(acc1==0 && acc2==3 &&((i+2>=xsize+1)||(int)get_state(f,i+2,j+1)!=0)){
									p.x=i-1;
									p.y=j+1;
									g_array_append_val(g,p);
								}
								if(acc1==3 && acc2==0 &&((i+2>=xsize+1)||(int)get_state(f,i+2,j-1)!=0)){
									p.x=i-1;
									p.y=j-1;
									g_array_append_val(g,p);
								}
							}
						}
					}
				}
			}
		}
	}
}

/**
this procedure tests some special cases which are not taken care of by pair_logic
for region: -1 not known 0 open 1 possible mine 2 mine
*/
void pair_logic_special(const field * f,GArray * g){
	int i,j,k,l,xsize,ysize;
	xsize=field_get_xsize(f);
	ysize=field_get_ysize(f);
	int current,tmpCurrent, tmpUndis;
	position p;
	p.click=1;
	for(i=1;i<=xsize;i++){
		for(j=1;j<=ysize;j++){
			if(get_state(f,i,j)==1 && get_value(f,i,j)!=0){
				current=get_value(f,i,j);
				for(k=-1;k<2;k++){
					for(l=-1;l<2;l++){
						if(get_state(f,i+k,j+l)==2)current--;
					}
				}

				/*can still be optimized regarding the if statemants right-left, top-bottom, etc*/
				/*left top case*/ 
				if(i-1>0 && j-1>0 && (j+1<=ysize || i+1<=xsize) && \
						get_state(f,i-1,j-1)==1 && get_value(f,i-1,j-1)!=0){
					tmpCurrent=get_value(f,i-1,j-1);
					for(k=-1;k<2;k++){
						for(l=-1;l<2;l++){
							if(get_state(f,i-1+k,j-1+l)==2)tmpCurrent--;	
						}
					}
					tmpUndis=0;
					for(k=-1;k<2;k++){
						if(get_state(f,i-2,j-1+k)==0)tmpUndis++;
						if(get_state(f,i-1+k,j-2)==0)tmpUndis++;
					}
					if(tmpUndis==0 && tmpCurrent==current){
						for(k=-1;k<1;k++){
							if(i+1<xsize+1 && get_state(f,i+1,j+k)==0){
								p.x=i+1;
								p.y=j+k;
								g_array_append_val(g,p);
							}
							if(j+1<xsize+1 && get_state(f,i+k,j+1)==0){
								p.x=i+k;
								p.y=j+1;
								g_array_append_val(g,p);
							}
						}
						if(j+1<ysize+1 && i+1<xsize+1 && get_state(f,i+1,j+1)==0){
							p.x=i+1;
							p.y=j+1;
							g_array_append_val(g,p);
						}
					}
				}
				/*left case*/
				if(i-1>0 && i+1<xsize+1 && get_state(f,i-1,j)==1 && get_value(f,i-1,j)!=0){
					tmpCurrent=get_value(f,i-1,j);
					for(k=-1;k<2;k++){
						for(l=-1;l<2;l++){
							if(get_state(f,i-1+k,j+l)==2)tmpCurrent--;
						}
					}
					tmpUndis=0;
					for(k=-1;k<2;k++){
						if(get_state(f,i-2,j+k)==0)tmpUndis++;
					}
					if(tmpUndis==0 && tmpCurrent==current){
						for(k=-1;k<2;k++){
							if(get_state(f,i+1,j+k)==0){
								p.x=i+1;
								p.y=j+k;
								g_array_append_val(g,p);
							}
						}
					}
				}
				/*left bottom case*/
				if(i-1>0 && j+1<ysize+1 && (i+1<xsize+1 ||j-1>0) && \
						get_state(f,i-1,j+1)==1 && get_value(f,i-1,j+1)!=0){
					tmpCurrent=get_value(f,i-1,j+1);
					for(k=-1;k<2;k++){
						for(l=-1;l<2;l++){
							if(get_state(f,i-1+k,j+1+l)==2)tmpCurrent--;	
						}
					}
					tmpUndis=0;
					for(k=-1;k<2;k++){
						if(get_state(f,i-1+k,j+2)==0)tmpUndis++;
						if(get_state(f,i-2,j+1+k)==0)tmpUndis++;
					}
					if(tmpUndis==0 && tmpCurrent==current){
						for(k=0;k<2;k++){
							if(i+1<xsize+1 && get_state(f,i+1,j+k)==0){
								p.x=i+1;
								p.y=j+k;
								g_array_append_val(g,p);
							}
							if(j-1>0 && get_state(f,i-1+k,j-1)==0){
								p.x=i-1+k;
								p.y=j-1;
								g_array_append_val(g,p);
							}
						}
						if((i+1<xsize+1 && j-1>0) && get_state(f,i+1,j-1)==0){
							p.x=i+1;
							p.y=j-1;
							g_array_append_val(g,p);
						}
					}
				}
				/*bottom case*/
				if(j+1<ysize+1 && j-1>0 && get_state(f,i,j+1)==1 && get_value(f,i,j+1)!=0){
					tmpCurrent=get_value(f,i,j+1);
					for(k=-1;k<2;k++){
						for(l=-1;l<2;l++){
							if(get_state(f,i+k,j+1+l)==2)tmpCurrent--;	
						}
					}
					tmpUndis=0;
					for(k=-1;k<2;k++){
						if(get_state(f,i+k,j+2)==0)tmpUndis++;
					}
					if(tmpUndis==0 && tmpCurrent==current){
						for(k=-1;k<2;k++){
							if(get_state(f,i+k,j-1)==0){
								p.x=i+k;
								p.y=j-1;
								g_array_append_val(g,p);
							}
						}
					}
				}
				/*right bottom case*/
				if(i+1<xsize+1 && j+1<ysize+1 && (i-1>0 || j-1>0) && \
						get_state(f,i+1,j+1)==1 && get_value(f,i+1,j+1)!=0){
					tmpCurrent=get_value(f,i+1,j+1);
					for(k=-1;k<2;k++){
						for(l=-1;l<2;l++){
							if(get_state(f,i+1+k,j+1+l)==2)tmpCurrent--;	
						}
					}
					tmpUndis=0;
					for(k=-1;k<2;k++){
						if(get_state(f,i+1+k,j+2)==0)tmpUndis++;
						if(get_state(f,i+2,j+1+k)==0)tmpUndis++;
					}
					if(tmpUndis==0 && tmpCurrent==current){
						for(k=-1;k<1;k++){
							if(j-1>0 && get_state(f,i+1+k,j-1)==0){
								p.x=i+1+k;
								p.y=j-1;
								g_array_append_val(g,p);
							}
							if(i-1>0 && get_state(f,i-1,j+1+k)==0){
								p.x=i-1;
								p.y=j+1;
								g_array_append_val(g,p);
							}
						}
						if((i-1>0 && j-1>0) && get_state(f,i-1,j-1)==0){
							p.x=i-1;
							p.y=j-1;
							g_array_append_val(g,p);
						}
					}
				}
				/*right case*/
				if(i+1<xsize+1 && i-1>0 && get_state(f,i+1,j)==1 && get_value(f,i+1,j)!=0){
					tmpCurrent=get_value(f,i+1,j);
					for(k=-1;k<2;k++){
						for(l=-1;l<2;l++){
							if(get_state(f,i+1+k,j+l)==2)tmpCurrent--;	
						}
					}
					tmpUndis=0;
					for(k=-1;k<2;k++){
						if(get_state(f,i+2,j+k)==0)tmpUndis++;
					}
					if(tmpUndis==0 && tmpCurrent==current){
						for(k=-1;k<2;k++){
							if(get_state(f,i-1,j+k)==0){
								p.x=i-1;
								p.y=j+k;
								g_array_append_val(g,p);
							}
						}
					}
				}
				/*right top case*/
				if(i+1<xsize+1 && j-1>0 && (i-1>0|| j+1<ysize+1) && \
						get_state(f,i+1,j-1)==1 && get_value(f,i+1,j-1)!=0){
					tmpCurrent=get_value(f,i+1,j-1);
					for(k=-1;k<2;k++){
						for(l=-1;l<2;l++){
							if(get_state(f,i+1+k,j-1+l)==2)tmpCurrent--;	
						}
					}
					tmpUndis=0;
					for(k=-1;k<2;k++){
						if(get_state(f,i+2,j-1+k)==0)tmpUndis++;
						if(get_state(f,i+1+k,j-2)==0)tmpUndis++;
					}
					if(tmpUndis==0 && tmpCurrent==current){
						for(k=-1;k<1;k++){
							if(j+1>ysize+1 && get_state(f,i+1+k,j+1)==0){
								p.x=i+1+k;
								p.y=j+1;
								g_array_append_val(g,p);
							}
							if(i-1>0 && get_state(f,i-1,j+k)==0){
								p.x=i-1;
								p.y=j+k;
								g_array_append_val(g,p);
							}
						}
						if((i-1>0 &&  j+1<ysize+1) && get_state(f,i-1,j+1)==0){
							p.x=i-1;
							p.y=j+1;
							g_array_append_val(g,p);
						}
					}
				}
				/*top case*/
				if(j-1>0 && j+1<ysize+1 && get_state(f,i,j-1)==1 && get_value(f,i,j-1)!=0){
					tmpCurrent=get_value(f,i,j-1);
					for(k=-1;k<2;k++){
						for(l=-1;l<2;l++){
							if(get_state(f,i+k,j-1+l)==2)tmpCurrent--;	
						}
					}
					tmpUndis=0;
					for(k=-1;k<2;k++){
						if(get_state(f,i+k,j-2)==0)tmpUndis++;
					}
					if(tmpUndis==0 && tmpCurrent==current){
						for(k=-1;k<2;k++){
							if(get_state(f,i+k,j+1)==0){
								p.x=i+k;
								p.y=j+1;
								g_array_append_val(g,p);
							}
						}
					}
				}	
			}
		}
	}
}

