#include <stdlib.h>
#include <xdo.h>
#include <gtk/gtk.h>
#include "screenInteraction.h"

void mouse_click(int button,int x,int y){
	xdo_t *hndl = xdo_new(NULL);
	xdo_mousemove(hndl,x,y,0);
	xdo_click(hndl,CURRENTWINDOW,button);
	xdo_free(hndl);
}

void mouse_move(int x, int y){
	xdo_t *hndl = xdo_new(NULL);
	xdo_mousemove(hndl,x,y,0);
	xdo_free(hndl);
}

void mouse_position(int * x, int *y){
	int scrn;
	xdo_t *hndl = xdo_new(NULL);
	xdo_mouselocation(hndl, x, y,&scrn);
	xdo_free(hndl);
}

void mouse_position_click(int* button,int * x, int * y){
	*x=*y=-1;
	XEvent event;
	Display *display = XOpenDisplay(NULL);
	if (display == NULL) {
	fprintf(stderr, "Cannot connect to X server!\n");
	exit (EXIT_FAILURE);
	}
	Window root= XDefaultRootWindow(display);
	XGrabPointer(display, root, False, ButtonReleaseMask, GrabModeAsync,
		 GrabModeAsync, None, None, CurrentTime);

	XSelectInput(display, root, ButtonReleaseMask) ;
	while(1){
		XNextEvent(display,&event);
		switch(event.type){
			case ButtonRelease:
			switch(event.xbutton.button){
				case Button1:
				*x=event.xbutton.x;
				*y=event.xbutton.y;
				*button=(int)Button1;
				break;

				case Button3:
				*x=event.xbutton.x;
				*y=event.xbutton.y;
				*button=(int)Button3;
				break;

				default:

				break;
			}	
		break;

		default:

       		break;
    		}
    	if(*x>=0 && *y>=0)break;
	}
	XCloseDisplay(display);
}

int screenshot(char * path){

	GdkWindow *root_window;
	GdkPixbuf *screenshot;
	gint x_orig, y_orig;
	gint width, height;

	root_window = gdk_get_default_root_window ();
	width=gdk_window_get_width(root_window);     
	height=gdk_window_get_height(root_window);
	gdk_window_get_origin (root_window, &x_orig, &y_orig);
	screenshot = gdk_pixbuf_get_from_drawable (NULL, root_window, NULL, x_orig, y_orig, 0, 0, width, height);
	
	gdk_pixbuf_save(screenshot,path,"png", NULL,NULL);  /*error handling still needs to be implemented*/

	return 1;
}
