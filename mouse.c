#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h> 
void enable_mouse_reporting() {
    printf("\033[?1003h"); // Enable mouse reporting
    fflush(stdout);
}

void disable_mouse_reporting() {
    printf("\033[?1003l"); // Disable mouse reporting
    fflush(stdout);
}

void set_raw_mode(int fd) {
    struct termios term;
    tcgetattr(fd, &term);
    term.c_lflag &= ~(ECHO | ICANON); // Disable canonical mode and echo
    tcsetattr(fd, TCSANOW, &term);
}

void reset_mode(int fd) {
    struct termios term;
    tcgetattr(fd, &term);
    term.c_lflag |= (ECHO | ICANON); // Enable canonical mode and echo
    tcsetattr(fd, TCSANOW, &term);
}

int main() {
    set_raw_mode(STDIN_FILENO);
    enable_mouse_reporting();

    printf("Click anywhere in the terminal to get mouse coordinates.\n");
    printf("Press 'q' to quit.\n");
    fflush(stdout);

    while (1) {
        char buf[6];
        ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));
        if (len > 0 && buf[0] == '\033' && buf[1] == '[') {
            if (buf[2] == 'M') {
                int x, y;

		    char *text = "Hello World";
                if (len >= 6) {
			system("clear");
                    x = buf[4] - ' ' - 1; // Convert from ASCII to coordinate
                    y = buf[5] - ' ' - 1; // Convert from ASCII to coordinate
		    
		    if((x-(strlen(text)/2)>1 && y>1)){
		    	for(int i=0;i<y;i++){
		    		printf("\n");
		    	}
		    	fflush(stdout);
		    	for(int i=0;i<x-(strlen(text))/2;i++){
		    		printf(" ");
		    	}
		    	fflush(stdout);
		    	printf("%s",text);
		    	fflush(stdout);
		    }
                }
            }
        }
        if (buf[0] == 'q') {
            break;
        }
    }

    disable_mouse_reporting();
    reset_mode(STDIN_FILENO);

    return 0;
}

