#include <assert.h>
#include <xdo.h>

#include "screenInteraction.h"
#include "imageRecognition.h"

/**
@brief detect_corner
tries to detect a corner and will be recursivly called. The x 
and y coordinates of a click generated by the user are passed as argument
and will contain the coordinates of the corner on success.
@param [in] img pointer to IplImage
@param [in,out] x pointer to x coordinate
@param [in,out] y pointer to y coordinate
@parma [in] depth indicates how many times detect_corner 
was alread called
@return 1 on succes 0 on failure
*/
static int detect_corner(const IplImage * img,int *x,int *y,int depth){
	unsigned char grey,left,top,diagonal;
	if(depth>100){
		return 0;
	}
	grey=CV_IMAGE_ELEM(img,uchar,*y,*x);
	left=CV_IMAGE_ELEM(img,uchar,*y,*x-1);
	top=CV_IMAGE_ELEM(img,uchar,*y-1,*x);
	diagonal=CV_IMAGE_ELEM(img,uchar,*y-1,*x-1);
	if(grey==255 && left<125 && top <125 && diagonal<125){
		return 1;
	}
	if(grey==255 && left<125 && diagonal<125 && top >125){
		*y=*y-1;
		return detect_corner(img,x,y,depth+1);
	}
	if(grey==255 && left>125 && diagonal<125 && top<125){
		*x=*x-1;
		return detect_corner(img,x,y,depth+1);
	}
	*x=*x-1;
	*y=*y-1;
	return detect_corner(img,x,y,depth+1);
}

/**
@brief detect_square_size
detects the square_size of minefield.
@param [in] img pointer to IplImage
@param [in] xcoord x coordinate of top left corner
@param [in] ycoord y coordinate of top left corner
@param [in] xsize  x dimesion of field
@return the sqaure_size
*/
static float detect_square_size(const IplImage * img, int xcoord,int ycoord, int xsize){
		unsigned char left,right;
		int x=xcoord;	
		int count=0;
		int extreme= img->width;
		while(count<xsize && x<extreme){
				left=CV_IMAGE_ELEM(img,uchar,ycoord,x);
				right=CV_IMAGE_ELEM(img,uchar,ycoord,x+1);
				if(left<130 && right==255) count++;
				x++;
		}
		printf("x == %d - xcoord == %d count== %d\n",x,xcoord,count);
		if(x<extreme){
				return (float)(((float)x-(float)xcoord)/xsize);
		}
		return -1;
}

int calibrating(minefield * mf,int xsize){
	int xclick, yclick,button,res;	
	screenshot("screenshot.png");
	printf("Please open the top left corner of the minefield!\n");
	mouse_position_click(&button, &xclick, &yclick);
	IplImage * img = cvLoadImage("screenshot.png",CV_LOAD_IMAGE_GRAYSCALE);
	if(!img){
		printf("Could not load image file: %s\n","screenshot.png");
		return -1;
	}
	if(!detect_corner(img, &xclick, &yclick,0)){
		printf("Could not detect corner of image");
		cvReleaseImage(&img);
		return -2;
	}
	mf->x_left=xclick;
	mf->y_top=yclick;
	printf("corner detected at %d %d \n",xclick,yclick);
	float sq_si=detect_square_size(img,xclick,yclick+5,xsize);
	if(sq_si<0){
			printf("Error calculating SQUARE_SIZE\n");
			cvReleaseImage(&img);
			return -3;
	}else{
			printf("SQUARE_SIZE calculated as %f\n",sq_si);
			mf->square_size=sq_si;
	}

	cvReleaseImage(&img);
	return 1;
}
	

void init_recognition(minefield * mf,int xsize, int ysize, int nbMines){	
	mf->fi=malloc(sizeof(field));
	field_init_version2(mf->fi,xsize, ysize,nbMines);
	mf->x_old=-1;
	mf->y_old=-1;
}

void free_recognition(minefield *mf){
	field_free(mf->fi);
	free(mf->fi);
}

void new_game(minefield *mf){
	field_new_game(mf->fi);
	mf->x_old=-1;
	mf->y_old=-1;
}

void move_mouse_out(minefield *mf){
	mouse_move(mf->x_left-25,mf->y_top-25);
	mf->x_old=mf->x_left-25;
	mf->y_old=mf->y_top-25;
}

/**
@brief detect_square_feature
detects the state and the value if open of a given square in an Image.
@param [in] img pointer to IplImage
@param [in] x pointer to x coordinate of the middle of the square
@param [in] y pointer to y coordinate of the middle of the square
@param [in] SQUARE_SIZE 
@return values 0-8 for 0-8 if square is opn square,-1 for a Flag, 10 undiscovered,-10 unknown or game over
*/
static int detect_square_feature(const IplImage * img, int x, int y,float SQUARE_SIZE){
	int i,j;
	int blue,green,red;
	blue=green=red=0;

	int xleft  	 = x-(int)((SQUARE_SIZE)/2);
	int xright   = x+(int)((SQUARE_SIZE)/2);
	int ytop     = y-(int)((SQUARE_SIZE)/2);
	int ybottom  = y+(int)((SQUARE_SIZE)/2);

	/*image data*/
	
	int height    = ybottom-ytop;
	int width     = xright-xleft;
	int channels  = img->nChannels;
		
	for(i=xleft;i<xright;i++){
		for(j=ytop;j<ybottom;j++){

			blue  +=(int)CV_IMAGE_ELEM(img,uchar,j,(i*channels));
			green +=(int)CV_IMAGE_ELEM(img,uchar,j,(i*channels)+1);
			red   +=(int)CV_IMAGE_ELEM(img,uchar,j,(i*channels)+2);
	
		}
	}

	blue   =(int)(blue/(width*height));
	green  =(int)(green/(width*height));
	red    =(int)(red/(width*height));

	/*0 and undis*/
	if((blue>170 && blue<205)&&(green>170 && green<205)&&(red>170 && red<205)&&(blue==green)&&(green==red)){
		blue=green=red=0;
		int xleft =x-(SQUARE_SIZE/2);
		int ytop  =y-(SQUARE_SIZE/2);
		for(i=xleft;i<xleft+(int)SQUARE_SIZE;i++){
			for(j=ytop;j<ytop+4;j++){

				blue  +=(int)CV_IMAGE_ELEM(img,uchar,j,(i*channels));
				green +=(int)CV_IMAGE_ELEM(img,uchar,j,(i*channels)+1);
				red   +=(int)CV_IMAGE_ELEM(img,uchar,j,(i*channels)+2);

			}
		}
		for(i=xleft;i<xleft+4;i++){
			for(j=ytop;j<ytop+(int)SQUARE_SIZE;j++){

				blue  +=(int)CV_IMAGE_ELEM(img,uchar,j,(i*channels));
				green +=(int)CV_IMAGE_ELEM(img,uchar,j,(i*channels)+1);
				red   +=(int)CV_IMAGE_ELEM(img,uchar,j,(i*channels)+2);

			}
		}
		blue  =(int)(blue/(8*SQUARE_SIZE));
		green =(int)(green/(8*SQUARE_SIZE));
		red   =(int)(red/(8*SQUARE_SIZE));
		
		if(blue>190 && green>190 && red>190){	
			return 10;
		}else{
			return 0;
		}
	}
	/* 1 */
	if((blue>178 && blue<210)&&(green>142 && green<170)&&(red>142 && red<170)){
		return 1;
	}
	/* 2 */
	if((blue>115 && blue<142)&&(green>155 && green<180)&&(red>115 && red<142)){
		return 2;
	}
	/* 3 */
	if((blue>120 && blue<145)&&(green>120 && green<145)&&(red>180 && red<215)){
		return 3;
	}
	/* 4 */
	if((blue>157 && blue<178)&&(green>129 && green<158)&&(red>129 && red<158)){
		return 4;
	}
	/* 5 */
	if((blue>120 && blue<138)&&(green>120 && green<138)&&(red>154 && red<179)){
		return 5;
	}
	/* 6 */
	if((blue>157 && blue<179)&&(green>157 && green<179)&&(red>123 && red<150)){
		return 6;
	}
	/* 7 */
	if(blue<155 && green<155 && red<155 && blue==green && green==red){
		return 7;
	}
	/* 8 */
	if((blue>124 && blue<134)&&(green>122 && green<132)&&(red>124 && red<134)){
		return 8;
	}
	/* Flag */
	if((blue>140 && blue<181)&&(green>140 && green<181)&&(red>158 && red<195)){
		return -1;
	}

	return -10;
}

int read_field(const char * screenshotpath, minefield * mf){
	assert(mf->square_size>0);
	float SQUARE_SIZE=mf->square_size;
	int i,j;
	int feature;
	int xfirstcase=mf->x_left;
	int yfirstcase=mf->y_top;
	IplImage * img = cvLoadImage(screenshotpath,CV_LOAD_IMAGE_COLOR);
	if(!img){
		printf("Could not load image file: %s\n",screenshotpath);
		return -2;
	}
	int xsize=field_get_xsize(mf->fi);
	int ysize=field_get_ysize(mf->fi);
	for(i=0;i<xsize;i++){
		for(j=0;j<ysize;j++){

			feature=detect_square_feature(img,xfirstcase+round((i*SQUARE_SIZE)+(SQUARE_SIZE/2)),
				yfirstcase+round(j*SQUARE_SIZE+(SQUARE_SIZE/2)),SQUARE_SIZE);
			if(0<=feature && feature<9){	
				set_state(mf->fi,i+1,j+1,1);
				set_value(mf->fi,i+1,j+1,feature);
			}
			if(feature==-1){
				set_state(mf->fi,i+1,j+1,2);
			}
			if(feature==-2){
				cvReleaseImage(&img);
				return -1;
			}
			if(feature==-10){
				cvReleaseImage(&img);
				return 0;
			}
		}
	}
	cvReleaseImage(&img);
	return 1;
}

int mouse_action(const position *p,minefield * mf)
{
	assert(mf->square_size>0);
	float SQUARE_SIZE=mf->square_size;
	int xfirstcase=round(mf->x_left+(SQUARE_SIZE/2));
	int yfirstcase=round(mf->y_top+(SQUARE_SIZE/2));
	int xcoord=round(xfirstcase+((p->x-1)*SQUARE_SIZE));
	int ycoord=round(yfirstcase+((p->y-1)*SQUARE_SIZE));
	int x,y;
	mouse_position(&x,&y);
	if((mf->x_old==-1 && mf->y_old==-1)||(x==mf->x_old && y==mf->y_old)){
		if(p->click==1){
			mouse_click(Button1,xcoord,ycoord);
		}else{
			mouse_click(Button3,xcoord,ycoord);
		}
		mf->x_old=xcoord;
		mf->y_old=ycoord;
		return 1;
	}
	return 0;
}

int mouse_click_let_it_play(minefield* mf, int xcoord,int ycoord){
		int x,y;
		mouse_position(&x,&y);
		if((mf->x_old==-1 && mf->y_old==-1)||(x==mf->x_old && y==mf->y_old)){
			mouse_click(Button1,xcoord,ycoord);
			mf->x_old=xcoord;
			mf->y_old=ycoord;
			return 1;
		}
		return 0;
}

/*float calibrating_test(char * path, int *x, int *y,int xsize){
	int res, xpos, ypos;
	float sq_si; 
	xpos=*x;
	ypos=*y;
	IplImage* img = cvLoadImage(path,CV_LOAD_IMAGE_GRAYSCALE);
	if(!img) printf("Could not load image file: %s\n",path);
	res=detect_corner(img,&xpos,&ypos,0);
	if(res){
		printf("corner detected at %d %d \n",xpos,ypos);
	}else{
		printf("failed to detect corner");
		cvReleaseImage(&img);
		return -1;
	}
	sq_si=detect_square_size(img,xpos,ypos+5,xsize);
	printf("Square size is of size %f\n",sq_si);
	cvReleaseImage(&img);
	SQUARE_SIZE=sq_si;
	*x=xpos;
	*y=ypos;
	return sq_si;
}*/


