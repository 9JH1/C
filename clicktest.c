#include <stdio.h>
// include 
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h> 
//include
 

//include

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

void quitHandler(){
    disable_mouse_reporting();
    reset_mode(STDIN_FILENO);
    exit(0);
}

//include
void HandleClick(){
    printf("handleClickBALLS\n");
}

// call with single array, runs function if clicked
void awaitClickPreciseDynamicText(char* text void (*callHandler)()){
    set_raw_mode(STDIN_FILENO);
    enable_mouse_reporting();
    fflush(stdout);
    while (1) {
        fflush(stdout);
        char buf[6];
        ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));
        if (len > 0 && buf[0] == '\033' && buf[1] == '[') {
            if (buf[2] == 'M') {
                if (len >= 6) {
                    int button = buf[3] - ' ' - 1; // Mouse button code
                    int x = buf[4] - ' ' - 1; // Convert from ASCII to coordinate
                    int y = buf[5] - ' ' - 1; // Convert from ASCII to coordinate

                    // figure out where the cursor is
                    // figure out cursor location and if clicked run function this 
                    // is not good but it might work
                    if (button == 0 || button == 1 || button == 2) {
                        if(xF == x && yF == y){
                            disable_mouse_reporting();
                            reset_mode(STDIN_FILENO);
                            callHandler();
                            break;
                        }
                    }
                }
            }
        }
    }
}

int main(){
    awaitClickPreciseStatic("HELLO WORLD",HandleClick);
}

