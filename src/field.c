#include "field.h"

int field_get_xsize(const field * f){
	return f->x-2;
}

int field_get_ysize(const field * f){
	return f->y-2;
}

void field_init(field * f, int x, int y, int mines){
	assert(x>=1 && y>=1);
	int i,j,k,l;
	f->area=malloc((x+2)*(y+2)*sizeof(char));
	f->display=malloc((x+2)*(y+2)*sizeof(char));
	f->x=x+2;
	f->y=y+2;
	f->nbMines=mines;
	for(i=0; i<f->x;i++){
		for(j=0;j<f->y;j++){
			f->area[i*f->y+j]=0;
			if(i==0 || i==f->x-1 || j==0 || j==f->y-1){
				f->display[i*f->y+j]=1;
			}else{
				f->display[i*f->y+j]=0;
			}
		}
	}
	i=0;
	while(i<mines){
		j=(rand()%x)+1;
		k=(rand()%y)+1;
		if(f->area[j*(y+2)+k]==0){
			f->area[j*(y+2)+k]=-1;
			i++;
		}
	}
	for(i=1;i<x+1;i++){
		for(j=1;j<y+1;j++){
			if(f->area[i*(y+2)+j]!=-1){
				for(k=i-1;k<i+2;k++){
					for(l=j-1;l<j+2;l++){
						if(f->area[k*(y+2)+l]==-1){
							f->area[i*(y+2)+j]++;
						}
					}
				}
			}
		}
	}
}

void field_init_version2(field * f,int x, int y, int mines){
	assert(x>=1 && y>=1);
	int i,j;
	f->area=malloc((x+2)*(y+2)*sizeof(char));
	f->display=malloc((x+2)*(y+2)*sizeof(char));
	f->x=x+2;
	f->y=y+2;
	f->nbMines=mines;
	for(i=0; i<f->x;i++){
		for(j=0;j<f->y;j++){
			f->area[i*f->y+j]=0;
			if(i==0 || i==f->x-1 || j==0 || j==f->y-1){
				f->display[i*f->y+j]=1;
			}else{
				f->display[i*f->y+j]=0;
			}
		}
	}
}

void field_new_game(field *f){
	int i,j;
	for(i=0; i<f->x;i++){
		for(j=0;j<f->y;j++){
			f->area[i*f->y+j]=0;
			if(i==0 || i==f->x-1 || j==0 || j==f->y-1){
				f->display[i*f->y+j]=1;
			}else{
				f->display[i*f->y+j]=0;
			}
		}
	}
}

void field_free(field * f){
	free(f->area);
	free(f->display);
	f->x=0;
	f->y=0;
}

void discover(field * f, int x, int y){
	assert(x>=0 && y>=0 && x<=f->x-2 && y<=f->y-2);
	int i,j;
	for(i=x-1;i<x+2;i++){
		for(j=y-1;j<y+2;j++){
			if((i!=x || j!=y) && (int)get_state(f,i,j)==0 && (int)get_value(f,i,j)!=-1 \
				&& i>0 && i<f->x-1 && j>0 && j<f->y-1 ){
				set_state(f,i,j,1);
				if((int)get_value(f,i,j)==0){
					discover(f,i,j);
				}
			}
		}
	}
}

char get_state(const field * f,int x, int y){
	assert(x>=0 && y>=0 && x<=f->x && y<=f->y);
	return f->display[x*f->y+y];
}

void set_state(field *f, int x ,int y, char state){
	assert(x>=0 && y>=0 && x<=f->x && y<=f->y);
	f->display[x*f->y+y]=state;
}

char get_value(const field * f, int x ,int y){
	assert(x>=0 && y>=0 && x<=f->x && y<=f->y);
	return f->area[x*f->y+y];
		
}

void set_value(field * f, int x, int y, char value){
	assert(x>=0 && y>=0 && x<=f->x && y<=f->y);
	f->area[x*f->y+y]=value;
}
		

int game_state(const field * f){
	int i,j;
	int count=0;
	for(i=1;i<f->x-1;i++){
		for(j=1;j<f->y-1;j++){
			if(f->display[i*f->y+j]==1 && f->area[i*f->y+j]==-1){
				return -1;
			}
			if(f->display[i*f->y+j]==0 || f->display[i*f->y+j]==2){
				count++;
			}
		}
	}
	if(count==(f->nbMines)){
		return 1;
	}
	return 0;
}

int game_state_reg(const field * f){
	int i,j;
	int countOpen=0;
	for(i=1;i<f->x-1;i++){
		for(j=1;j<f->y-1;j++){
			if(f->display[i*f->y+j]==1){
				countOpen++;
			}
		}
	}
	int neededOpen=((f->x-2)*(f->y-2))-(f->nbMines);
	if(neededOpen==countOpen){
		return 1;
	}
	return 0;
}

void display(const field * f){
	int i,j;
	for(i=0;i<f->x-1;i++)printf("%d ",i);
	printf("\n");
	for(i=1;i<f->y-1;i++){
		printf("%d ",i);
		for(j=1;j<f->x-1;j++){
			if(f->display[j*f->y+i]==1){
				printf("%d ",f->area[j*f->y+i]);
			}else{
				if(f->display[j*f->y+i]==2){
					printf("# ");
				}else{
					printf("* ");
				}
			}
		}
		printf("\n");
	}
}

void display_area(const field * f){
	int i,j;
	for(i=0;i<f->x-1;i++)printf("%d ",i);
	printf("\n");
	for(i=1;i<f->y-1;i++){
		printf("%d ",i);
		for(j=1;j<f->x-1;j++){
			if(f->area[j*f->y+i]==-1){
				printf("%d ",f->area[j*f->y+i]);
			}else{
				printf("%d ", f->area[j*f->y+i]);
			}
		}
		printf("\n");
	}
}

int flagged(const field*f){
	int i,j,flagged=0;
	for(i=1;i<f->y-1;i++){
		for(j=1;j<f->x-1;j++){
			if(f->display[j*f->y+i]==2)flagged++;
		}
	}
	return flagged;
}

void field_test(){
	char temp,temp1;
	field f;
	field_init(&f,10,10,10);
	printf("field_init.. OK\n");
	set_state(&f,1,4,1);
	set_state(&f,1,5,1);
	temp=get_state(&f,1,4);
	temp1=get_state(&f,10,10);
	assert(temp==1 || temp1==0);
	printf("get_state and set_state ... OK\n");
	display(&f);
	printf("\n");
	display_area(&f);
	printf("\n");
	printf("displays ... OK \n");
	field_free(&f);
}
