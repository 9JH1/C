#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 100

void render_color_text(
		/*  FOREGROUND */
		int foreground_r,
		int foreground_g,
		int foreground_b,

		/*  BACKGROUND */
		int background_r,
		int background_g,
		int background_b,
	       	/*     TEXT    */	
		char *text
		){
	/* concatanate into one string */
    	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm%s\033[0m",
		    foreground_r, 
		    foreground_g, 
		    foreground_b, 
		    background_r, 
		    background_g, 
		    background_b, 
		    text
	);
}



int main(){
	char array_buttons[][MAX_ARRAY_SIZE] = {
		"Hello",
		"Merry", 
		"Jim",

	};
	int array_buttons_index=0;
	char *text_logo_space = "See You Tomorrow";
	int oldRow, oldCol;
	while(1){
		// loop forever
		struct winsize w;
    		ioctl(0, TIOCGWINSZ, &w);

		if(w.ws_row != oldRow || w.ws_col != oldCol){ 
    	
			system("clear");
			fflush(stdout);
    			// handle the index number
			array_buttons_index++;
			if(array_buttons_index > sizeof(array_buttons)/sizeof(array_buttons[0])-1){
				// if index is over its max set it to lowest
				array_buttons_index = 0;
			} else if (array_buttons_index<0){
				// if index is under its min set it to the highest
				array_buttons_index=sizeof(array_buttons)/sizeof(array_buttons[0])-1;
			}
			for(int i=0;i<(sizeof(array_buttons)/sizeof(array_buttons[0]));i++){
				if(i == array_buttons_index){
					//show a highlight
					// --COLOR
					render_color_text(0,0,0,255,100,255,array_buttons[i]);
				} else {
					// button is normal
					render_color_text(0,0,0,255,255,255,array_buttons[i]);
				}
				if(i<(sizeof(array_buttons)/sizeof(array_buttons[0]))-1){
					// this is the seperator color
					render_color_text(0,0,0,150,150,150," ");
				}	
			}
			fflush(stdout);
			// time to draw the rest of the bar
			int array_buttons_size_full=0;
			// edited potion sorry for layout
			array_buttons_size_full += (sizeof(array_buttons)/sizeof(array_buttons[0]))-1;
			// end of edit
			for(int i=0;i<(sizeof(array_buttons)/sizeof(array_buttons[0]));i++){
				array_buttons_size_full += strlen(array_buttons[i]);
			}
			int width_top_bar = (w.ws_col-array_buttons_size_full)-strlen(text_logo_space);
			if(width_top_bar<0){
				// the window cannot fit all of the objects on the screen
				// this should be handled with cutting off either the 
				// text logo space or the buttons i dont want to so it stays 
				// like this

				width_top_bar=0;
			}
			for(int i=0;i<width_top_bar;i++){
				// this is the color of the space between the buttons and the logo
				render_color_text(0,0,0,150,150,150," ");	
			}
			fflush(stdout);
			render_color_text(0,0,0,255,255,255,text_logo_space);
			printf("\n");
			// time to render the main application window
			//
			// minus three, one for the top bar one for the
			// center bar and one for the button row which 
			// needs to be rendered seperatly
			int half_width_main = (w.ws_row-3)/2;
			for(int i=0;i<half_width_main;i++){
				//render first char as white
				render_color_text(0,0,0,255,255,255," ");
				
				// fill inside with red
				for(int ii=0;ii<w.ws_col-2;ii++){
					render_color_text(0,0,0,0,0,255," ");
				}

				// render last char in white
				render_color_text(0,0,0,255,255,255," ");

			}
			fflush(stdout);
			//print the center text line
			char *main_center_text = "Good Morning!";
			int main_center_text_width = (w.ws_col-2-strlen(main_center_text))/2;
			render_color_text(0,0,0,255,255,255," ");
			for(int i=0;i<main_center_text_width;i++){
				render_color_text(0,0,0,0,0,255," ");
			}
			render_color_text(0,0,0,255,255,255,main_center_text);
			fflush(stdout);
			main_center_text_width = w.ws_col-main_center_text_width-strlen(main_center_text)-2;
			if(main_center_text_width < 0){
				// terminal cannot fit objects onto screen
				main_center_text_width = 0;
			}
			for(int i=0;i<main_center_text_width;i++){
				render_color_text(0,0,0,0,0,255," ");
			}
			render_color_text(0,0,0,255,255,255, " ");
			// render the bottom half of the main content
			for(int i=0;i<w.ws_row-half_width_main-3;i++){
				// render the first char as white
				render_color_text(0,0,0,255,255,255," ");

				//fill inside with red
				for(int ii=0;ii<w.ws_col-2;ii++){
					render_color_text(0,0,0,0,0,255," ");
				}
				

				// render the last char in white
				render_color_text(0,0,0,255,255,255," ");
			}
			// this lets us have another row of the terminal
			for(int i=0;i<w.ws_col-1;i++){
				render_color_text(0,0,0,255,255,255," ");
			}
			render_color_text(0,0,0,255,255,255," \r");
			fflush(stdout);

			oldRow = w.ws_row;
			oldCol = w.ws_col;
		}
	}
	return 0;

}
