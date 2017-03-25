#include <gtk/gtk.h>

#include <time.h>
#include "solver1.h"
#include "imageRecognition.h"
#include "screenInteraction.h"

/**
@brief dataGtk
contains all the information about the current game as well
as most of the widgets.
*/
typedef struct{
		GtkWindow* window;
		GtkCheckButton* probaCheckButton;
		GtkScale* timestampScale;
		GtkEntry* xEntry;
		GtkEntry* yEntry;
		GtkEntry* nbMinesEntry;
		minefield* mf;
		gint* errorCode;
		gchar* string;
		gboolean calibrated;
		gboolean freeStructures;
		gint xsize;
		gint ysize;
}dataGtk;

/**
@brief show_info_not_yet_implemented
shows a little popup window which notifies the user that a certain feature is not
yet implemented.
@param widget pointer to GtkWidget
@param window pointer to window
*/
static void show_info_not_yet_implemented(GtkWidget * widget, gpointer window)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Not yet implemented");
  gtk_window_set_title(GTK_WINDOW(dialog), "Info");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

/**
@brief show_given_info
shows a little popup window with the message that is contained in 
the dataGtk structure passed as parameter.
@param widget pointer to GtkWidget
@param pdata pointer to dataGtk
*/
static void show_given_info(GtkWidget* widget, gpointer pdata){
	dataGtk *data=pdata;
	GtkWindow* window=data->window;
	gchar* string =data->string;

	GtkWidget*dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            string);
	gtk_window_set_title(GTK_WINDOW(dialog), "Info");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

/**
@brief error_code_handling
handles errors returned by any part of the application and shows a respective message.
* errorCode		meaning
* -1			Error loading image file
* -2			Error detecting corner of minefield
* -3 			Error calculating square_size
* -4 			Error analysing image file
@param widget pointer to GtkWidget
@param pdata pointer to dataGtk
*/

static void error_code_handling(GtkWidget* widget, gpointer pdata){
	dataGtk*data=pdata;	
	GtkWindow* window=data->window;
	gint* errorCode =data->errorCode;
	gchar * string;
	/* switch through all the error codes*/
	switch(*errorCode) {
			case -1:
				string = g_strdup("Error loading image file\n");
				break;
			case -2:
				string = g_strdup("Error detecting corner of minefield\n");
				break;
			case -3:
				string = g_strdup("Error calculating the square size\n");
				break;
			case -4:
				string = g_strdup("Error analysing image file\n");
				break;
			default:
				string = g_strdup("An unknown error occured\n");

	}
	GtkWidget*dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            string);
	gtk_window_set_title(GTK_WINDOW(dialog), "Error-Message");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);	
	g_free(string);
}

/**
@brief show_warning_entry_values
shows a warning if one of the entries is not a number or is negative.
@param window pointer to window 
*/
static void show_warning_entry_values(gpointer window)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "You need to give positiv numbers as entries\n");
  gtk_window_set_title(GTK_WINDOW(dialog), "");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

/* 
@brief close_app
opens a dialog box and asks if the user really wants to quit the application 
@param window pointer to window 
@return TRUE is yes FALSE if no
*/
static gboolean close_app(gpointer window)
{
   	GtkWidget *dialog;
	gint result;

   /* Create the widgets */
   dialog = gtk_dialog_new_with_buttons ("Close the application?",
                                         window,
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_NO,
										 GTK_RESPONSE_NO,
										 GTK_STOCK_YES,
										 GTK_RESPONSE_YES,
                                         NULL);

	gtk_window_set_default_size(GTK_WINDOW(dialog),230,40);
   /* Ensure that the dialog box is destroyed when the user responds */
   result=gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);
   if(result==GTK_RESPONSE_YES){
		return FALSE;
   }
   return TRUE;
}

/**
@brief check_entries
checks if the entries are positive numbers.
@param pdata pointer to dataGtk
@return TRUE is yes FALSE if no
*/
static gboolean check_entries(gpointer pdata){
	dataGtk * data=pdata;
	
	GtkEntryBuffer* buffer;
	gchar * number;

	buffer=gtk_entry_get_buffer(GTK_ENTRY(data->xEntry));
	number=gtk_entry_buffer_get_text(buffer);
	if(0>=g_ascii_strtoll(number,NULL,10)){
		return FALSE;
	}

	buffer=gtk_entry_get_buffer(GTK_ENTRY(data->yEntry));
	number=gtk_entry_buffer_get_text(buffer);
	if(0>=g_ascii_strtoll(number,NULL,10)){
		return FALSE;
	}

	buffer=gtk_entry_get_buffer(GTK_ENTRY(data->nbMinesEntry));
	number=gtk_entry_buffer_get_text(buffer);
	if(0>=g_ascii_strtoll(number,NULL,10)){
		return FALSE;
	}
	
	return TRUE;
}

/**
@brief calibrate_appli
calibrates the application.
@param widget pointer to GtkWidget
@param pdata pointer to dataGtk
*/
static void calibrate_appli(GtkWidget *widget, gpointer pdata){
	GtkWidget* dummy=NULL;	
	dataGtk*data=(dataGtk*)pdata;
	GtkWindow* window=data->window;	
	if(!check_entries(pdata)){
		show_warning_entry_values(window);
	}else{
		data->string=g_strdup("Please click on the left top corner of \n the minefield after closing this popup!");
		show_given_info(dummy,data);
		g_free(data->string);
		data->string= NULL;

		minefield * mf= data->mf;	
		GtkEntryBuffer* buffer=gtk_entry_get_buffer(GTK_ENTRY(data->xEntry));
		gchar * number=gtk_entry_buffer_get_text(buffer);

		gint res=calibrating(mf,g_ascii_strtoll(number,NULL,10));
		if(res<0){
			data->errorCode=&res;
			error_code_handling(dummy,data);
			data->errorCode=NULL;
		}else{
			data->calibrated=TRUE;
			data->string=g_strdup("The application was succesful calibrated\n");
			show_given_info(dummy,data);
			g_free(data->string);
			data->string=NULL;

			GtkEntryBuffer* buffer;
			gchar * number;
			gint nbMines;

			buffer=gtk_entry_get_buffer(GTK_ENTRY(data->xEntry));
			number=gtk_entry_buffer_get_text(buffer);
			data->xsize=g_ascii_strtoll(number,NULL,10);	

			buffer=gtk_entry_get_buffer(GTK_ENTRY(data->yEntry));
			number=gtk_entry_buffer_get_text(buffer);
			data->ysize=g_ascii_strtoll(number,NULL,10);	
		}
	}
}

/**
@brief start_appli
starts to solve game if possible.
@param widget pointer to GtkWidget
@param pdata pointer to dataGtk
*/
static void start_appli(GtkWidget * widget, gpointer pdata){
	dataGtk*data=(dataGtk*)pdata;
	GtkWidget *dummy=NULL;
	if(data->calibrated==FALSE){
		data->string=g_strdup("You need to calibrate the application!\n");
		show_given_info(dummy,data);
		g_free(data->string);
		data->string=NULL;
	}else{
		GtkEntry* xEntry=data->xEntry;
		GtkEntry* yEntry=data->yEntry;
		GtkEntryBuffer* buffer;
		gchar * number;
		gint x,y;

		buffer=gtk_entry_get_buffer(GTK_ENTRY(xEntry));
		number=gtk_entry_buffer_get_text(buffer);
		x=g_ascii_strtoll(number,NULL,10);	

		buffer=gtk_entry_get_buffer(GTK_ENTRY(yEntry));
		number=gtk_entry_buffer_get_text(buffer);
		y=g_ascii_strtoll(number,NULL,10);	

		if(x==data->xsize && y==data->ysize){	
			if(data->freeStructures==FALSE){
				GtkEntryBuffer* buffer;
				gchar * number;
				gint nbMines;

				buffer=gtk_entry_get_buffer(GTK_ENTRY(data->nbMinesEntry));
				number=gtk_entry_buffer_get_text(buffer);
				nbMines=g_ascii_strtoll(number,NULL,10);

				data->freeStructures=TRUE;
			
				init_recognition(data->mf,data->xsize,data->ysize,nbMines); 
			}
			gint res;
			if(gtk_toggle_button_get_active(data->probaCheckButton)){
				res=solver_proba(data->mf,(float)gtk_range_get_value(GTK_RANGE(data->timestampScale)));
				if(res<2){
					if(res==1){
						data->string=g_strdup("The game was succesfully solved\n");
					}else{
						data->string=g_strdup("The game was not succesfully solved\n");
					}
					show_given_info(dummy,data);
					g_free(data->string);
					data->string=NULL;
					free_recognition(data->mf);
					data->freeStructures=FALSE;
				}
				/*maybe implement a better ErrorCode recognition
				meaning that imageRecognition should distinguish
				between reconizing error and and a bomb*/
				/*show_info_not_yet_implemented(dummy,data->window);*/
			}else{
				res=solver(data->mf,(float)gtk_range_get_value(GTK_RANGE(data->timestampScale)));
				if(res<0){
					data->errorCode=&res;
					error_code_handling(dummy,data);
					data->errorCode=NULL;
					free_recognition(data->mf);
					data->calibrated=FALSE;
					data->freeStructures=FALSE;
				}
			}
		}else{
			if(data->freeStructures){
				free_recognition(data->mf);
				data->freeStructures=FALSE;
			}
			data->calibrated=FALSE;
			data->xsize=-1;
			data->ysize=-1;
			data->string=g_strdup("The minefield dimensions have changed!\nPlease calibrate the application beforehand!");
			show_given_info(dummy,data);
			g_free(data->string);
			data->string=NULL;
		}
	}
}

/**
@brief new_game_callback
initializes a new_game in the field structure if the dimesions 
have not chagned.
@param widget pointer to GtkWidget
@param pdata pointer to dataGtk 
*/
static void new_game_callback(GtkWidget * widget, gpointer pdata){
	dataGtk*data=(dataGtk*)pdata;
	if(data->calibrated==FALSE){
		GtkWidget *dummy=NULL;
		data->string=g_strdup("You need to calibrate the application!\n");
		show_given_info(dummy,data);
		g_free(data->string);
		data->string=NULL;
	}else{
			new_game(data->mf);
	}
}

/**
@brief let_it_play
tries to solve a game until fully solved. 
@param widget pointer to GtkWidget
@param pdata pointer to dataGtk 
*/
static void let_it_play(GtkWidget *widget, gpointer pdata ){
	dataGtk*data=(dataGtk*)pdata;
	GtkWidget *dummy=NULL;
	if(data->calibrated==FALSE){
		data->string=g_strdup("You need to calibrate the application!\n");
		show_given_info(dummy,data);
		g_free(data->string);
		data->string=NULL;
	}else{

		/*initialization part*/
		GtkEntry* xEntry=data->xEntry;
		GtkEntry* yEntry=data->yEntry;
		GtkEntryBuffer* buffer;
		gchar * number;
		gint x,y;

		buffer=gtk_entry_get_buffer(GTK_ENTRY(xEntry));
		number=gtk_entry_buffer_get_text(buffer);
		x=g_ascii_strtoll(number,NULL,10);	

		buffer=gtk_entry_get_buffer(GTK_ENTRY(yEntry));
		number=gtk_entry_buffer_get_text(buffer);
		y=g_ascii_strtoll(number,NULL,10);	

		if(x==data->xsize && y==data->ysize){	
			int ng_x,ng_y,buttondummy,res=0,cntn=1;
			data->string=g_strdup("Please click on the new game button\nafter closing this popup!\n\
It will not work correctly if you \ndon't click on the correct location.\n");
			show_given_info(dummy,pdata);
			g_free(data->string);
			data->string=NULL;

			mouse_position_click(&buttondummy,&ng_x,&ng_y);
			/*implement test that the coordinates of new button are corrcect: 
			open left corner check if open, new game check if closed*/

			if(data->freeStructures==FALSE){
				GtkEntryBuffer* buffer;
				gchar * number;
				gint nbMines;

				buffer=gtk_entry_get_buffer(GTK_ENTRY(data->nbMinesEntry));
				number=gtk_entry_buffer_get_text(buffer);
				nbMines=g_ascii_strtoll(number,NULL,10);
			
				data->freeStructures=TRUE;
			
				init_recognition(data->mf,data->xsize,data->ysize,nbMines); 
			}else{
				new_game(data->mf);
			}

			/*doesn't recognize the fact that if a normal game was started we don't reintialize the field
			but click on the new game button afterwards*/
			/* gets stuck in infinite loop if errorCode was returned*/	
			while(res!=1 && res!=2 && cntn==1){
					res=solver_proba(data->mf,(float)gtk_range_get_value(GTK_RANGE(data->timestampScale)));
					if(res!=2){
						cntn=mouse_click_let_it_play(data->mf,ng_x,ng_y);
					}
					new_game(data->mf);
			}

			if(res==1){
				free_recognition(data->mf);
				data->freeStructures=FALSE;
			}

		}else{
			if(data->freeStructures){
				free_recognition(data->mf);
				data->freeStructures=FALSE;
			}
			data->calibrated=FALSE;
			data->xsize=-1;
			data->ysize=-1;
			data->string=g_strdup("The minefield dimensions have changed! \n \
							Please calibrate the application beforehand!");
			show_given_info(dummy,data);
			g_free(data->string);
			data->string=NULL;
		}
	}
}

/**
@brief delete_event
checks if the user really wants to close the application.
@param widget pointer to GtkWidget
@param event pointer to GdkEvent
@param window pointer to window
@return TRUE is yes FALSE if no
*/
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   window )
{
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */
    g_print ("delete event occurred\n");

    return close_app(window);
}

/**
@brief destroy
quits the application.
@param widget pointer to GtkWidget
@param data NULL pointer
*/
static void destroy( GtkWidget *widget,
                     gpointer data)
{
    	gtk_main_quit ();
}


void minesweeper_solver()
{
    /* GtkWidget is the storage type for widgets */
	/*main window*/
    GtkWidget *window;
	/*buttons*/
	GtkWidget *calibrate;
	GtkWidget *start;
	GtkWidget *newGame;
	GtkWidget *letItPlay;
	/*organizing*/
	GtkWidget *table;
	/*Timestamp*/
	GtkWidget *timestampLabel;
	GtkWidget *timestampScale;
	/*size*/
	GtkWidget *xLabel;
	GtkWidget *xEntry;
	GtkWidget *yLabel;
	GtkWidget *yEntry;
	GtkWidget *nbMinesLabel;
	GtkWidget *nbMinesEntry;
	/*probability*/
	GtkWidget *probaCheckButton;

	/*minefield*/
	minefield mf;

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

   	/* Setting some properties of the main window */ 
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), "Minesweeper solver");	
	
	/*setting up the timestampeWidgets*/
	timestampLabel= gtk_label_new("Timestamp in s");
	timestampScale = gtk_vscale_new_with_range(0.001,2,0.001);
	/*gtk_scale_new_with_range (GTK_ORIENTATION_VERTICAL,0.001,2,0.001); used in GTK+ 3*/

	/*game information*/
	xLabel = gtk_label_new("Horizontal size");
	yLabel = gtk_label_new("Vertical size");
	nbMinesLabel= gtk_label_new("Number of mines");

	xEntry = gtk_entry_new();
	yEntry = gtk_entry_new();
	nbMinesEntry = gtk_entry_new();

	gtk_entry_set_text((GtkEntry*)xEntry,"30");
	gtk_entry_set_text((GtkEntry*)yEntry,"16");
	gtk_entry_set_text((GtkEntry*)nbMinesEntry,"99");

	
	/*proba*/
	probaCheckButton = gtk_check_button_new_with_label("with probability");
	
	/*adding the pointers of all the widgets needed in some function to a dataGtk structure
	* index		value			content
	* 0 		GtkWindow*		main_window
	* 1         GtkScale*  		timestampScale
	* 2			GtkEntry*		xEntry
	* 3			GtkEntry*		yEntry
	* 4			GtkEntry*		nbMinesEntry
	* 5	 		minefield *		mf		
	* 6 		gint * 			errorCode
	* 7			gchar *			string	
	*/
	dataGtk data;

	data.window=window;
	data.probaCheckButton=probaCheckButton;
	data.timestampScale=timestampScale;
	data.xEntry=xEntry;
	data.yEntry=yEntry;
	data.nbMinesEntry=nbMinesEntry;
	data.mf=&mf;
	data.calibrated=FALSE;
	data.freeStructures=FALSE;
	data.xsize=-1;
	data.ysize=-1;



	/*connecting the close callback functions*/
    g_signal_connect (window, "delete-event",G_CALLBACK (delete_event), window);
    
    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);

   
    /* Creates various buttons.  */
	calibrate = gtk_button_new_with_label("Calibrate");
	start = gtk_button_new_with_label("Start");
	newGame = gtk_button_new_with_label("New game");
	letItPlay = gtk_button_new_with_label("Let it play"); 
    
    /* When the button receives the "clicked" signal, it will call the
     * function hello() passing it NULL as its argument.  The hello()
     * function is defined above. */
    g_signal_connect (G_OBJECT(calibrate), "clicked", G_CALLBACK (calibrate_appli),&data );
    g_signal_connect (G_OBJECT(start), "clicked", G_CALLBACK (start_appli), &data);
    g_signal_connect (G_OBJECT(newGame), "clicked", G_CALLBACK (new_game_callback), &data);
    g_signal_connect (G_OBJECT(letItPlay), "clicked", G_CALLBACK (let_it_play), &data);

	/*organize things*/

	table= gtk_table_new(9,2,TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 2);
	gtk_table_set_col_spacings(GTK_TABLE(table), 2);	

	gtk_table_attach(GTK_TABLE(table), probaCheckButton, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), xLabel, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), xEntry, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), yLabel, 0, 1, 3, 4, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), yEntry, 0, 1, 4, 5, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), nbMinesLabel, 0, 1, 5, 6, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), nbMinesEntry, 0, 1, 6, 7, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), timestampLabel, 1, 2, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), timestampScale, 1, 2, 1, 7, GTK_FILL, GTK_FILL, 3, 3);

	gtk_table_attach(GTK_TABLE(table), calibrate, 0, 1, 7, 8, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), start, 1, 2, 7, 8, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), letItPlay, 0, 1, 8, 9, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), newGame, 1, 2, 8, 9, GTK_FILL, GTK_FILL, 3, 3);

    /* This packs the buttons into the window (a gtk container). */
    gtk_container_add (GTK_CONTAINER (window), table);
    

    /* finally show the window */
    gtk_widget_show_all (window);
    
    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();
	
	/* still needs some variable of when to free this and when not*/
	if(data.freeStructures){
		free_recognition(&mf);
	}
}
