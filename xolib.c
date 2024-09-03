#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>


void printc(
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

int getScreen(int rows,int cols){
		
		struct winsize window;
    		ioctl(0, TIOCGWINSZ, &window);
		cols = window.ws_col;
		rows = window.ws_row;
		return rows, cols;
}

char *take_full_input(const char *prompt, int LARGEST_INPUT) {
    char buffer[LARGEST_INPUT];
    char *input;

    // Display the prompt
    printf("%s", prompt);

    // Read the input
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Allocate memory for the input string
        input = malloc(strlen(buffer) + 1);
        if (input == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return NULL; // Return NULL to indicate an error
        }

        // Copy the input to the allocated memory
        strcpy(input, buffer);
        return input;
    } else {
        // Handle error: Input not successfully read
        fprintf(stderr, "Error reading input.\n");
        return NULL; // Return NULL to indicate an error
    }
}
