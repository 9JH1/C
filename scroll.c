#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

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

    printf("Scroll in the terminal to get mouse scroll events.\n");
    printf("Press 'q' to quit.\n");
    fflush(stdout);
	int scrollCount=0;
    while (1) {
        char buf[6];
        ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));
        if (len > 0 && buf[0] == '\033' && buf[1] == '[') {
            // Print raw buffer for debugging
            for (int i = 0; i < len; i++) {
            }
            printf("\n");

            if (buf[2] == 'M') {
                // Mouse event
                if (len >= 6) {
                    int button = buf[3] - ' ' - 1; // Mouse button code
                    int x = buf[4] - ' ' - 1; // Convert from ASCII to coordinate
                    int y = buf[5] - ' ' - 1; // Convert from ASCII to coordinate

                    // Print decoded values
		    if(button==63){scrollCount++;}
		    if(button==64){scrollCount--;}
		    printf("%d",scrollCount);
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

